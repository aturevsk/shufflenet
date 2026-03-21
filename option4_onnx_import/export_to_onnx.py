#!/usr/bin/env python3
"""Export ShuffleNet V2 PyTorch Model to ONNX Format.

Loads the .pt2 ExportedProgram, reconstructs a standard ShuffleNet V2
nn.Module, transfers weights, and exports to ONNX.

Usage:
    python3 export_to_onnx.py
"""

import os
import sys
import time
from pathlib import Path

import torch
import torch.nn as nn
import numpy as np


def main():
    script_dir = Path(__file__).resolve().parent
    model_path = script_dir / ".." / "shufflenet_exported.pt2"
    model_path = model_path.resolve()
    onnx_path = script_dir / "shufflenet_v2.onnx"

    print("=" * 60)
    print(" ShuffleNet V2: PyTorch to ONNX Export")
    print("=" * 60)

    if not model_path.exists():
        print(f"ERROR: Model file not found: {model_path}")
        sys.exit(1)

    # Step 1: Load ExportedProgram and extract weights
    print(f"\n[1/4] Loading ExportedProgram from {model_path}")
    ep = torch.export.load(str(model_path))

    # Extract state dict from ExportedProgram
    pt2_state = {}
    for name, param in ep.named_parameters():
        pt2_state[name] = param.detach()
    for name, buf in ep.named_buffers():
        pt2_state[name] = buf.detach()
    print(f"  Extracted {len(pt2_state)} parameters/buffers")

    # Step 2: Reconstruct standard ShuffleNet V2
    print("\n[2/4] Reconstructing ShuffleNet V2 nn.Module")
    from torchvision.models import shufflenet_v2_x1_0
    model = shufflenet_v2_x1_0(weights=None)

    # Transfer weights
    model_state = model.state_dict()
    matched = 0
    for key in model_state:
        if key in pt2_state:
            model_state[key] = pt2_state[key]
            matched += 1
    model.load_state_dict(model_state)
    model.eval()
    print(f"  Matched {matched}/{len(model_state)} parameters")
    total_params = sum(p.numel() for p in model.parameters())
    print(f"  Total parameters: {total_params:,}")

    # Step 3: Test inference
    print("\n[3/4] Running reference inference")
    dummy_input = torch.randn(1, 3, 224, 224)
    with torch.no_grad():
        ref_output = model(dummy_input)
    print(f"  Output shape: {ref_output.shape}")
    top5 = ref_output.topk(5).indices[0].tolist()
    print(f"  Top-5 classes: {top5}")

    # Step 4: Export to ONNX
    print(f"\n[4/4] Exporting to ONNX (opset 17)")
    t0 = time.perf_counter()
    # Use dynamo=False to get legacy exporter that produces ONNX IR version 9
    # compatible with MATLAB R2026a
    torch.onnx.export(
        model,
        dummy_input,
        str(onnx_path),
        opset_version=17,
        input_names=["input"],
        output_names=["output"],
        dynamic_axes={
            "input": {0: "batch_size"},
            "output": {0: "batch_size"},
        },
        do_constant_folding=True,
        verbose=False,
        dynamo=False,
    )
    export_time = time.perf_counter() - t0
    file_size = onnx_path.stat().st_size
    print(f"  Export time: {export_time:.2f}s")
    print(f"  Output: {onnx_path}")
    print(f"  Size: {file_size / 1e6:.2f} MB")

    # Verify
    try:
        import onnx
        onnx_model = onnx.load(str(onnx_path))
        onnx.checker.check_model(onnx_model)
        ops = sorted(set(n.op_type for n in onnx_model.graph.node))
        print(f"  ONNX check: PASSED")
        print(f"  Nodes: {len(onnx_model.graph.node)}")
        print(f"  Ops ({len(ops)}): {', '.join(ops)}")
    except ImportError:
        print("  Skipping ONNX validation (onnx package not installed)")

    print(f"\n{'=' * 60}")
    print(f" Export complete! Next: run import_onnx_and_generate.m in MATLAB")
    print(f"{'=' * 60}")


if __name__ == "__main__":
    main()
