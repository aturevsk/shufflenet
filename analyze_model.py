"""Analyze a ShuffleNet .pt2 exported model."""

import torch
from collections import Counter, OrderedDict

MODEL_PATH = "/Users/arkadiyturevskiy/Documents/Claude/PyTorch_Import_2/Shufflenet/shufflenet_exported.pt2"

print("=" * 80)
print("Loading model from:", MODEL_PATH)
print("=" * 80)

ep = torch.export.load(MODEL_PATH)
gm = ep.module()

# 1. Print the graph/architecture
print("\n" + "=" * 80)
print("1. MODEL GRAPH (ExportedProgram)")
print("=" * 80)
print(ep)

# 2. Print the graph module code
print("\n" + "=" * 80)
print("2. GRAPH MODULE CODE")
print("=" * 80)
print(ep.graph_module.code)

# 3. Layer names, types, and shapes from state dict
print("\n" + "=" * 80)
print("3. ALL PARAMETERS / BUFFERS: NAME, SHAPE, DTYPE")
print("=" * 80)

state_dict = ep.state_dict
if not state_dict:
    # Try alternative access
    state_dict = dict(gm.named_parameters())
    state_dict.update(dict(gm.named_buffers()))

total_params = 0
trainable_params = 0

print(f"\n{'Name':<70} {'Shape':<25} {'Dtype':<12} {'Numel':>10}")
print("-" * 120)

# Collect from named_parameters and named_buffers
param_info = []
for name, param in gm.named_parameters():
    numel = param.numel()
    total_params += numel
    trainable_params += numel if param.requires_grad else 0
    param_info.append((name, tuple(param.shape), str(param.dtype), numel, "param"))

for name, buf in gm.named_buffers():
    numel = buf.numel()
    param_info.append((name, tuple(buf.shape), str(buf.dtype), numel, "buffer"))

for name, shape, dtype, numel, kind in param_info:
    print(f"{name:<70} {str(shape):<25} {dtype:<12} {numel:>10}  ({kind})")

# 4. Total parameter count
print("\n" + "=" * 80)
print("4. PARAMETER COUNT SUMMARY")
print("=" * 80)
print(f"Total parameters:     {total_params:>12,}")
print(f"Total buffers:        {len([x for x in param_info if x[4] == 'buffer']):>12,}")
print(f"Total param tensors:  {len([x for x in param_info if x[4] == 'param']):>12,}")
print(f"Model size (approx):  {total_params * 4 / (1024*1024):.2f} MB (assuming float32)")

# 5. Input/output shapes
print("\n" + "=" * 80)
print("5. INPUT / OUTPUT SHAPES")
print("=" * 80)

# From graph signature
sig = ep.graph_signature
print(f"\nGraph signature input specs ({len(sig.input_specs)} total):")
for spec in sig.input_specs:
    print(f"  {spec}")

print(f"\nGraph signature output specs ({len(sig.output_specs)} total):")
for spec in sig.output_specs:
    print(f"  {spec}")

# Try running a dummy forward to confirm shapes
print("\nAttempting dummy forward pass to confirm shapes...")
try:
    dummy_input = torch.randn(1, 3, 224, 224)
    with torch.no_grad():
        output = gm(dummy_input)
    if isinstance(output, torch.Tensor):
        print(f"  Input shape:  {dummy_input.shape}")
        print(f"  Output shape: {output.shape}")
    elif isinstance(output, (tuple, list)):
        print(f"  Input shape:  {dummy_input.shape}")
        for i, o in enumerate(output):
            if isinstance(o, torch.Tensor):
                print(f"  Output[{i}] shape: {o.shape}")
            else:
                print(f"  Output[{i}]: {type(o)}")
    else:
        print(f"  Input shape:  {dummy_input.shape}")
        print(f"  Output type:  {type(output)}")
except Exception as e:
    print(f"  Forward pass failed: {e}")

# 6. Unique operation types
print("\n" + "=" * 80)
print("6. UNIQUE OPERATION TYPES IN GRAPH")
print("=" * 80)

op_counter = Counter()
for node in ep.graph_module.graph.nodes:
    if node.op == "call_function":
        op_counter[str(node.target)] += 1
    else:
        op_counter[f"[{node.op}]"] += 1

print(f"\n{'Operation':<65} {'Count':>6}")
print("-" * 72)
for op, count in sorted(op_counter.items(), key=lambda x: -x[1]):
    print(f"{op:<65} {count:>6}")

print(f"\nTotal unique operation types: {len(op_counter)}")
print(f"Total nodes in graph:        {sum(op_counter.values())}")

# 7. Graph nodes detail
print("\n" + "=" * 80)
print("7. GRAPH NODES DETAIL (first 80 nodes)")
print("=" * 80)
for i, node in enumerate(ep.graph_module.graph.nodes):
    if i >= 80:
        print(f"  ... ({sum(1 for _ in ep.graph_module.graph.nodes) - 80} more nodes)")
        break
    meta_shape = ""
    if "val" in node.meta:
        val = node.meta["val"]
        if isinstance(val, torch.Tensor):
            meta_shape = f"shape={tuple(val.shape)}, dtype={val.dtype}"
        elif isinstance(val, (tuple, list)):
            parts = []
            for v in val:
                if isinstance(v, torch.Tensor):
                    parts.append(f"{tuple(v.shape)}")
            if parts:
                meta_shape = f"shapes=[{', '.join(parts)}]"
    print(f"  [{i:3d}] op={node.op:<16} name={node.name:<45} target={str(node.target)[:60]:<60} {meta_shape}")

print("\n" + "=" * 80)
print("ANALYSIS COMPLETE")
print("=" * 80)
