# WasmEdge LFX Mentorship – Cover Letter

**Applicant:** Anurag Jain  
**Email:** anuragj4711@gmail.com  
**GitHub:** https://github.com/me-jain-anurag/  
**Phone:** +91-9864803743  
**Project:** Module instance dependency tree in WASM store (2026 Term 1)

---

## Cover Letter

To the WasmEdge Mentors,

I am Anurag Jain, an undergraduate student in Information Science and Engineering at Dayananda Sagar College of Engineering, Bengaluru. I discovered the WasmEdge LFX Mentorship while exploring CNCF projects, and the *Module Instance Dependency Tree* project immediately captured my interest due to its focus on runtime safety, lifecycle management, and internal correctness guarantees.

This project sits at the intersection of my core strengths: systems programming and graph-based reasoning.

### Why I am a strong fit for this project

**Algorithmic and Graph-Theoretic Strength**  
Managing module dependencies is fundamentally a graph problem. As a Codeforces Specialist (max 1495) and ICPC 2025–26 Regionalist, I have extensive experience working with directed graphs, DAG validation, cycle detection, and topological safety checks. Designing a dependency structure that is both correct and efficient aligns well with my background.

**Relevant Systems Experience**  
- **Go-Blockchain:** Built a blockchain from scratch, implementing strict state consistency checks, cryptographic validation, and controlled lifecycle management. This closely parallels the need for maintaining a consistent and crash-free module store in WasmEdge.
- **Maze Generator (C++):** Implemented DFS- and BFS-based graph traversal with attention to memory usage and correctness, directly applicable to dependency tree traversal and reference validation.

**Prepared and Motivated Contributor**  
Although I am new to the WasmEdge codebase, I have already built the runtime from source and completed the pre-tests using the WasmEdge C API. While working on the `lib.wasm` → `calc.wasm` example, I directly observed how deleting a provider module before its dependents leads to crashes, reinforcing the importance of this project. My NPTEL distinctions (Top 1% in Algorithms) reflect my ability to quickly understand and apply complex technical material.

### Project Understanding

Currently, WasmEdge allows modules to import instances from other registered modules, but these relationships are implicit. The runtime does not formally track use–definition chains between module instances. As a result, deleting a provider module while dependent modules remain instantiated can lead to dangling references and undefined behavior.

My objective is to introduce explicit dependency tracking within the StoreManager so that module lifecycles are enforced safely and predictably.

---

## Proposal: Module Instance Dependency Tree

### 1. Problem Statement

WasmEdge registers module instances in a central store managed by `WasmEdge::Runtime::StoreManager`. Import relationships are resolved during instantiation, but not recorded structurally. This allows unsafe deletion of modules that are still in use, leading to segmentation faults or undefined behavior.

### 2. Proposed Solution

I propose implementing a **reference-aware dependency graph** inside the StoreManager.

**Core concepts:**
- Each module instance is represented as a node.
- Directed edges represent dependency relationships (consumer → provider).
- The graph is used to enforce safe deletion and lifecycle rules.

**Key Components:**
- **Dependency Node:** Tracks the module instance along with its dependencies and dependents.
- **Registration & Instantiation Hooks:** During module instantiation, imports are intercepted and edges are recorded in the graph.
- **Safe Deletion Guard:** When `unregisterModule` is called, the graph is queried. If the module has active dependents, deletion is rejected with a clear error (e.g., `WasmEdge_Result_InUse`).
- **Optional Extension:** Recursive or forced deletion, implemented only if approved by mentors.

---

## Execution Plan (12 Weeks)

**Phase 1: Analysis & Design (Weeks 1–2)**  
- Deep dive into `include/runtime/storemgr.h` to understand StoreManager responsibilities and module registration flow  
- Study `include/runtime/instance/module.h` to analyze how module instances expose imports and exports  
- Identify the exact import resolution path during instantiation  
- Design the dependency graph data structures and interfaces  
- Deliverable: Detailed design document / RFC for mentor review

**Phase 2: Core Implementation (Weeks 3–6)**  
- Implement the dependency graph (adjacency list + hash map for O(1) lookup)  
- Extend `StoreManager::registerModule` to initialize graph nodes  
- Hook into module instantiation to record dependency edges during import resolution  
- Milestone: Runtime can internally represent module dependency relationships

**Phase 3: Safety Enforcement & Edge Cases (Weeks 7–8)**  
- Implement safe deletion logic in `StoreManager::unregisterModule`  
- Add clear error reporting for dependency violations  
- Handle edge cases such as re-registration and partial failures  
- Optional: mentor-approved recursive deletion mechanism  
- Milestone: Unsafe deletion attempts are rejected instead of crashing

**Phase 4: Testing & Documentation (Weeks 9–12)**  
- Unit tests for dependency graph logic (cycle detection, edge cases)  
- Integration tests using `.wasm` modules similar to the pre-test setup  
- Validate memory safety and absence of dangling references  
- Documentation updates describing the dependency model and lifecycle guarantees

---

## Availability

I can dedicate **20-25 hours per week** consistently throughout the mentorship period. I have planned the work to align with my academic calendar while ensuring steady progress across all phases. This schedule allows sufficient time for implementation, testing, and mentor feedback without compromising code quality.

---

## Pre-test Checklist

- [x] Pre-test 1 (Python): Solved — Output `120903`  
- [x] Pre-test 2 (C API): Demonstrated `lib.wasm` → `calc.wasm` dependency and crash potential  
- [x] Mentorship policy read and agreed  

**Pre-test Repository:**  
https://github.com/me-jain-anurag/wasmedge-lfx-pretest

---

I am excited about the opportunity to contribute to WasmEdge by improving runtime stability through explicit dependency management. I look forward to working closely with the mentors and contributing a well-designed, thoroughly tested feature to the codebase.

Regards,  
**Anurag Jain**