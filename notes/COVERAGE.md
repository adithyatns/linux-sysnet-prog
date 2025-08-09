# Code Coverage Guide

This project enforces **100% line coverage** for all commits using both `gcovr` (terminal) and `lcov` (HTML).

---

## How Coverage Works

### Pre-Commit Hook
- The `.hooks/check_coverage.sh` script runs **before every commit**.
- It:
  1. Builds the project with coverage flags.
  2. Runs all tests.
  3. Generates:
     - `gcovr` terminal report (quick view of uncovered lines)
     - `lcov` HTML report (detailed view)
  4. Fails the commit if coverage is below **100%**.

---

## Coverage Commands

### View quick coverage in terminal
```bash
gcovr -r . --exclude 'test/' --txt --sort-uncovered
Generate detailed HTML report
bash
Copy
Edit
lcov --capture --directory build --output-file coverage/coverage.info
lcov --remove coverage/coverage.info '*/test/*' '/usr/*' --output-file coverage/coverage_filtered.info
genhtml coverage/coverage_filtered.info --output-directory coverage/html

build/coverage/html/index.html
```

### Tips for Maintaining 100% Coverage
Test all branches — success, failure, and edge cases.

Use negative tests to hit error-handling code.

Run pre-commit run --all-files before committing to check locally.

### Related Files
.hooks/check_coverage.sh – pre-commit hook for coverage enforcement
.pre-commit-config.yaml – hook configuration
