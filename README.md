# ShuffleNet V2 — Embedded C Code Generation for STM32F746G-Discovery

Comparison of **4 approaches** for generating embedded C code from a PyTorch ShuffleNet V2 1.0x classification model, targeting the **STM32F746G-Discovery** (ARM Cortex-M7 @ 216 MHz).

## [Interactive Results Explorer](https://aturevsk.github.io/shufflenet/)

## Model

| Spec | Value |
|------|-------|
| Architecture | ShuffleNet V2 1.0x |
| Parameters | 2,278,604 (8.69 MB float32) |
| Input | 3 x 224 x 224 (RGB) |
| Output | 1000 ImageNet classes |
| MACs | ~146M per inference |

## Options Compared

| Option | Method | Code Size | Lines of C | Status |
|--------|--------|-----------|------------|--------|
| 1 | Hand-crafted C99 | 71.5 KB | 1,660 | Complete |
| 2 | MATLAB Coder PyTorch SP (MLIR/TOSA) | 4,439 KB | 63,586 | Complete |
| 3 | importNetworkFromPyTorch + MATLAB Coder | ~4,400 KB | ~62,000 | Complete |
| 4 | ONNX Import + MATLAB Coder | 4,495 KB | 64,412 | Complete |

## 100-Test Numerical Equivalence

| Metric | Opt 3 (PT Import) | Opt 4 (ONNX) |
|--------|-------------------|---------------|
| Avg cosine similarity | 0.9589 | 0.9589 |
| Opt 3 vs Opt 4 | **Bit-identical** (0.0 error) | |
| Avg MATLAB inference | 27.4 ms | 58.3 ms |

## Project Structure

```
option1_handcrafted_c/     Hand-crafted C implementation
option2_pytorch_coder/     MATLAB Coder PyTorch SP workflow
option3_import_pytorch/    importNetworkFromPyTorch workflow
option4_onnx_import/       ONNX import workflow
equivalence_tests/         100-test validation suite
benchmark/                 Performance comparison
report/                    PDF report generator
webapp/                    Interactive results explorer
```

## Requirements

- MATLAB R2026a (with Deep Learning Toolbox, MATLAB Coder, Embedded Coder)
- Python 3.10+ with PyTorch, torchvision, numpy
- ARM toolchain (for Option 1 cross-compilation)

## Quick Start

```bash
# Generate reference test vectors
cd equivalence_tests && python3 generate_reference_data.py

# Run MATLAB equivalence tests
matlab -batch "run('equivalence_tests/run_full_100.m')"

# Generate PDF report
python3 report/generate_report.py
```

---
Generated with [Claude Code](https://claude.ai/claude-code) | March 2026
