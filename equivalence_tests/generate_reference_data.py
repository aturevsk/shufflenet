#!/usr/bin/env python3
"""Generate 100 Reference Test Vectors for Numerical Equivalence Validation.

Creates 100 random input tensors, runs them through the PyTorch ShuffleNet V2
model, and saves both inputs and reference outputs for cross-validation against
C and MATLAB implementations.

Test vector categories (100 total):
  - Tests  1-50: Standard random normal inputs (ImageNet-like normalized)
  - Tests 51-70: Uniform random inputs in [0, 1]
  - Tests 71-80: Edge cases — all zeros, all ones, large values, negatives
  - Tests 81-90: Structured patterns — gradients, checkerboards, single channels
  - Tests 91-100: Real-world-like — ImageNet mean/std normalized random

Outputs saved to test_vectors/ directory:
  - input_NNN.bin   — raw float32 input  (1x3x224x224 = 150528 floats)
  - output_NNN.bin  — raw float32 output (1x1000 floats)
  - reference_summary.csv — per-test statistics
  - test_metadata.json    — full test configuration

Usage:
    python3 generate_reference_data.py

Requirements:
    pip install torch torchvision numpy
"""

import json
import os
import sys
import time
import csv
from pathlib import Path

import numpy as np
import torch
from torchvision.models import shufflenet_v2_x1_0


# ── Configuration ─────────────────────────────────────────────────────
NUM_TESTS = 100
INPUT_SHAPE = (1, 3, 224, 224)
NUM_ELEMENTS_IN = 1 * 3 * 224 * 224   # 150528
NUM_ELEMENTS_OUT = 1000
SEED = 42

# ImageNet normalization constants
IMAGENET_MEAN = [0.485, 0.456, 0.406]
IMAGENET_STD  = [0.229, 0.224, 0.225]


def load_model(model_path: str) -> torch.nn.Module:
    """Load .pt2 ExportedProgram and reconstruct nn.Module."""
    print("[1/4] Loading model...")
    ep = torch.export.load(model_path)

    # Extract weights
    pt2_state = {}
    for name, param in ep.named_parameters():
        pt2_state[name] = param.detach()
    for name, buf in ep.named_buffers():
        pt2_state[name] = buf.detach()

    # Reconstruct standard ShuffleNet V2
    model = shufflenet_v2_x1_0(weights=None)
    model_state = model.state_dict()
    matched = 0
    for key in model_state:
        if key in pt2_state:
            model_state[key] = pt2_state[key]
            matched += 1
    model.load_state_dict(model_state)
    model.eval()
    print(f"      Loaded {matched}/{len(model_state)} parameters")
    return model


def create_test_inputs(rng: np.random.Generator) -> list:
    """Create 100 diverse test input tensors with descriptions."""
    tests = []

    # ── Tests 1-50: Standard random normal ────────────────────────
    for i in range(50):
        x = rng.standard_normal(INPUT_SHAPE).astype(np.float32)
        tests.append((x, f"random_normal_seed{SEED}_idx{i}"))

    # ── Tests 51-70: Uniform random [0,1] ────────────────────────
    for i in range(20):
        x = rng.uniform(0.0, 1.0, INPUT_SHAPE).astype(np.float32)
        tests.append((x, f"uniform_01_idx{i}"))

    # ── Tests 71-80: Edge cases ──────────────────────────────────
    edge_cases = [
        (np.zeros(INPUT_SHAPE, dtype=np.float32),
         "all_zeros"),
        (np.ones(INPUT_SHAPE, dtype=np.float32),
         "all_ones"),
        (-np.ones(INPUT_SHAPE, dtype=np.float32),
         "all_neg_ones"),
        (np.full(INPUT_SHAPE, 0.5, dtype=np.float32),
         "all_half"),
        (np.full(INPUT_SHAPE, 5.0, dtype=np.float32),
         "large_positive_5"),
        (np.full(INPUT_SHAPE, -5.0, dtype=np.float32),
         "large_negative_5"),
        (np.full(INPUT_SHAPE, 1e-6, dtype=np.float32),
         "very_small_positive"),
        (np.full(INPUT_SHAPE, -1e-6, dtype=np.float32),
         "very_small_negative"),
        (np.full(INPUT_SHAPE, 10.0, dtype=np.float32),
         "large_positive_10"),
        (np.eye(224, dtype=np.float32)[np.newaxis, np.newaxis, :, :].repeat(3, axis=1),
         "identity_matrix_pattern"),
    ]
    for x, desc in edge_cases:
        tests.append((x, desc))

    # ── Tests 81-90: Structured patterns ─────────────────────────
    # Horizontal gradient
    grad_h = np.linspace(0, 1, 224, dtype=np.float32)[np.newaxis, np.newaxis, np.newaxis, :]
    grad_h = np.broadcast_to(grad_h, INPUT_SHAPE).copy()
    tests.append((grad_h, "horizontal_gradient"))

    # Vertical gradient
    grad_v = np.linspace(0, 1, 224, dtype=np.float32)[np.newaxis, np.newaxis, :, np.newaxis]
    grad_v = np.broadcast_to(grad_v, INPUT_SHAPE).copy()
    tests.append((grad_v, "vertical_gradient"))

    # Checkerboard
    checker = np.zeros(INPUT_SHAPE, dtype=np.float32)
    for r in range(224):
        for c in range(224):
            if (r + c) % 2 == 0:
                checker[0, :, r, c] = 1.0
    tests.append((checker, "checkerboard"))

    # Single channel active (R only)
    r_only = np.zeros(INPUT_SHAPE, dtype=np.float32)
    r_only[0, 0, :, :] = rng.standard_normal((224, 224)).astype(np.float32)
    tests.append((r_only, "red_channel_only"))

    # Single channel active (G only)
    g_only = np.zeros(INPUT_SHAPE, dtype=np.float32)
    g_only[0, 1, :, :] = rng.standard_normal((224, 224)).astype(np.float32)
    tests.append((g_only, "green_channel_only"))

    # Single channel active (B only)
    b_only = np.zeros(INPUT_SHAPE, dtype=np.float32)
    b_only[0, 2, :, :] = rng.standard_normal((224, 224)).astype(np.float32)
    tests.append((b_only, "blue_channel_only"))

    # Center patch (small region non-zero)
    center = np.zeros(INPUT_SHAPE, dtype=np.float32)
    center[0, :, 96:128, 96:128] = rng.standard_normal((3, 32, 32)).astype(np.float32)
    tests.append((center, "center_patch_32x32"))

    # Diagonal stripe
    diag = np.zeros(INPUT_SHAPE, dtype=np.float32)
    for k in range(224):
        diag[0, :, k, k] = 1.0
        if k + 1 < 224:
            diag[0, :, k, k + 1] = 0.5
    tests.append((diag, "diagonal_stripe"))

    # Sinusoidal pattern
    x_coord = np.linspace(0, 4 * np.pi, 224, dtype=np.float32)
    y_coord = np.linspace(0, 4 * np.pi, 224, dtype=np.float32)
    xx, yy = np.meshgrid(x_coord, y_coord)
    sin_pat = np.sin(xx) * np.cos(yy)
    sin_input = np.zeros(INPUT_SHAPE, dtype=np.float32)
    sin_input[0, 0] = sin_pat
    sin_input[0, 1] = np.sin(xx + np.pi / 3) * np.cos(yy + np.pi / 3)
    sin_input[0, 2] = np.sin(xx + 2 * np.pi / 3) * np.cos(yy + 2 * np.pi / 3)
    tests.append((sin_input, "sinusoidal_rgb"))

    # High frequency noise
    hf = rng.standard_normal(INPUT_SHAPE).astype(np.float32) * 3.0
    tests.append((hf, "high_frequency_noise_3x"))

    # ── Tests 91-100: ImageNet-like normalized ───────────────────
    for i in range(10):
        # Simulate a "real" image: pixel values ~[0,1] then normalize
        img = rng.uniform(0.0, 1.0, INPUT_SHAPE).astype(np.float32)
        for c in range(3):
            img[0, c] = (img[0, c] - IMAGENET_MEAN[c]) / IMAGENET_STD[c]
        tests.append((img, f"imagenet_normalized_idx{i}"))

    assert len(tests) == NUM_TESTS, f"Expected {NUM_TESTS}, got {len(tests)}"
    return tests


def run_inference(model, input_np: np.ndarray) -> np.ndarray:
    """Run single inference and return output as numpy."""
    with torch.no_grad():
        input_t = torch.from_numpy(input_np)
        output_t = model(input_t)
    return output_t.numpy()


def main():
    script_dir = Path(__file__).resolve().parent
    project_dir = script_dir.parent
    model_path = str(project_dir / "shufflenet_exported.pt2")
    output_dir = script_dir / "test_vectors"
    output_dir.mkdir(exist_ok=True)

    print("=" * 70)
    print(" ShuffleNet V2 — 100-Test Numerical Equivalence Reference Generator")
    print("=" * 70)

    # Load model
    model = load_model(model_path)

    # Create test inputs
    print("\n[2/4] Creating 100 test input vectors...")
    rng = np.random.default_rng(SEED)
    tests = create_test_inputs(rng)
    print(f"      Created {len(tests)} test vectors")

    # Run inference and save results
    print("\n[3/4] Running PyTorch inference on all 100 test vectors...")
    results = []
    all_outputs = []
    t_total = 0.0

    for idx, (input_np, description) in enumerate(tests):
        # Save input
        input_path = output_dir / f"input_{idx + 1:03d}.bin"
        input_np.tofile(str(input_path))

        # Run inference
        t0 = time.perf_counter()
        output_np = run_inference(model, input_np)
        t1 = time.perf_counter()
        dt = t1 - t0
        t_total += dt

        # Save output
        output_path = output_dir / f"output_{idx + 1:03d}.bin"
        output_np.tofile(str(output_path))

        # Compute statistics
        top5_indices = np.argsort(output_np[0])[::-1][:5]
        top5_values = output_np[0][top5_indices]
        softmax = np.exp(output_np[0] - output_np[0].max())
        softmax /= softmax.sum()
        top1_prob = softmax[top5_indices[0]]

        result = {
            "test_id": idx + 1,
            "description": description,
            "input_min": float(input_np.min()),
            "input_max": float(input_np.max()),
            "input_mean": float(input_np.mean()),
            "input_std": float(input_np.std()),
            "output_min": float(output_np.min()),
            "output_max": float(output_np.max()),
            "output_mean": float(output_np.mean()),
            "output_std": float(output_np.std()),
            "output_l2_norm": float(np.linalg.norm(output_np)),
            "top1_class": int(top5_indices[0]),
            "top1_logit": float(top5_values[0]),
            "top1_prob": float(top1_prob),
            "top5_classes": top5_indices.tolist(),
            "top5_logits": top5_values.tolist(),
            "inference_time_ms": dt * 1000,
        }
        results.append(result)
        all_outputs.append(output_np)

        if (idx + 1) % 10 == 0:
            print(f"      Completed {idx + 1}/100  "
                  f"(last: {dt * 1000:.1f}ms, top1=class {top5_indices[0]})")

    avg_ms = t_total / NUM_TESTS * 1000
    print(f"      Total time: {t_total:.2f}s, Average: {avg_ms:.1f}ms/inference")

    # ── Save reference summary CSV ────────────────────────────────
    print("\n[4/4] Saving reference data...")

    csv_path = output_dir / "reference_summary.csv"
    csv_fields = [
        "test_id", "description",
        "input_min", "input_max", "input_mean", "input_std",
        "output_min", "output_max", "output_mean", "output_std", "output_l2_norm",
        "top1_class", "top1_logit", "top1_prob",
        "inference_time_ms",
    ]
    with open(csv_path, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=csv_fields, extrasaction="ignore")
        writer.writeheader()
        writer.writerows(results)
    print(f"      CSV summary: {csv_path}")

    # ── Save full metadata JSON ───────────────────────────────────
    meta = {
        "model": "ShuffleNet V2 1.0x",
        "source": str(model_path),
        "input_shape": list(INPUT_SHAPE),
        "output_size": NUM_ELEMENTS_OUT,
        "num_tests": NUM_TESTS,
        "seed": SEED,
        "dtype": "float32",
        "byte_order": "little-endian (native)",
        "input_file_format": "raw float32, CHW layout, 150528 elements",
        "output_file_format": "raw float32, 1000 elements",
        "pytorch_version": torch.__version__,
        "tests": results,
        "aggregate": {
            "avg_inference_ms": avg_ms,
            "total_inference_s": t_total,
        },
    }
    json_path = output_dir / "test_metadata.json"
    with open(json_path, "w") as f:
        json.dump(meta, f, indent=2)
    print(f"      JSON metadata: {json_path}")

    # ── Save concatenated outputs for quick MATLAB loading ────────
    # All 100 outputs stacked: shape (100, 1000)
    stacked = np.stack([o[0] for o in all_outputs], axis=0)  # (100, 1000)
    stacked_path = output_dir / "all_outputs_100x1000.bin"
    stacked.astype(np.float32).tofile(str(stacked_path))
    print(f"      Stacked outputs: {stacked_path} ({stacked.nbytes / 1024:.0f} KB)")

    # Also save stacked inputs for MATLAB: shape (100, 3, 224, 224)
    stacked_in = np.stack([t[0][0] for t in tests], axis=0)  # (100, 3, 224, 224)
    stacked_in_path = output_dir / "all_inputs_100x3x224x224.bin"
    stacked_in.astype(np.float32).tofile(str(stacked_in_path))
    print(f"      Stacked inputs:  {stacked_in_path} ({stacked_in.nbytes / 1024 / 1024:.0f} MB)")

    print(f"\n{'=' * 70}")
    print(f" Done! {NUM_TESTS} test vectors saved to {output_dir}/")
    print(f" Files: input_001..100.bin, output_001..100.bin")
    print(f" Summary: reference_summary.csv, test_metadata.json")
    print(f"{'=' * 70}")


if __name__ == "__main__":
    main()
