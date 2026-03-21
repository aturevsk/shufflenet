#!/usr/bin/env python3
"""Generate reference outputs directly from the .pt2 ExportedProgram.

The original generate_reference_data.py reconstructed a torchvision
ShuffleNet V2 model, which may have subtle differences from the .pt2.
This script uses the .pt2 directly for exact reference.
"""
import os, sys, json, time
import numpy as np
import torch
from pathlib import Path

NUM_TESTS = 100
SEED = 42

script_dir = Path(__file__).resolve().parent
model_path = script_dir / ".." / "shufflenet_exported.pt2"
test_dir = script_dir / "test_vectors"

print("Loading .pt2 ExportedProgram directly...")
ep = torch.export.load(str(model_path))

# Load existing inputs
print("Loading existing test inputs...")
inputs_raw = np.fromfile(str(test_dir / "all_inputs_100x3x224x224.bin"), dtype=np.float32)
inputs_raw = inputs_raw.reshape(NUM_TESTS, 3, 224, 224)

# Run inference through .pt2 directly
print("Running inference on 100 test vectors...")
outputs = []
for i in range(NUM_TESTS):
    x = torch.from_numpy(inputs_raw[i:i+1])
    with torch.no_grad():
        y = ep.module()(x)
    outputs.append(y.numpy())
    if (i+1) % 25 == 0:
        print(f"  {i+1}/100 done")

# Stack and save
stacked = np.stack([o[0] for o in outputs], axis=0)  # (100, 1000)
out_path = test_dir / "all_outputs_100x1000_pt2direct.bin"
stacked.astype(np.float32).tofile(str(out_path))
print(f"Saved: {out_path} ({stacked.nbytes / 1024:.0f} KB)")

# Also overwrite the original reference files
for i in range(NUM_TESTS):
    outputs[i].tofile(str(test_dir / f"output_{i+1:03d}.bin"))
stacked.astype(np.float32).tofile(str(test_dir / "all_outputs_100x1000.bin"))
print("Updated individual output files and stacked binary")

# Compare with old reference
old_path = test_dir / "all_outputs_100x1000.bin"
# We just overwrote it, so let's compute diff on the fly
old_outputs = np.fromfile(str(test_dir / "all_outputs_100x1000_pt2direct.bin"), dtype=np.float32).reshape(100,1000)
print(f"\nDone! Reference outputs now generated from .pt2 ExportedProgram directly.")
