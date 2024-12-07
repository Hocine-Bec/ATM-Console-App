# ATM Banking System: Course Project

## Project Context

This ATM banking system project serves as a practical exercise in functional programming principles using C++. The primary objective was to develop a comprehensive application while focusing on writing clean, maintainable code and applying functional programming concepts.

## Learning Objectives

The project was designed to:
- Demonstrate proficiency in procedural and functional programming techniques
- Practice modular code design
- Implement robust file handling and data management
- Develop a structured approach to software development
- Gain experience with:
  - Function composition
  - Immutable data structures
  - Separation of concerns
  - Pure functions and minimal state manipulation

## Key Functional Programming Concepts Applied

1. **Modular Function Design**
   - Small, focused functions with single responsibilities
   - Minimal side effects
   - Functions that can be easily composed and reused

2. **Data Transformation**
   - Use of vector transformations
   - String parsing and conversion functions
   - Stateless data processing

3. **File Handling as Pure Transformation**
   - Reading and writing files as pure data transformations
   - Minimal global state
   - Consistent data serialization and deserialization

## Project Structure and Design Patterns

- Emphasis on function-based architecture
- Use of enums for clear state management
- Separation of concerns between UI, data processing, and file management
- Minimal use of global variables
- Consistent error handling and input validation

## Technical Highlights

- Implemented without object-oriented programming
- Utilized C++ standard library effectively
- Demonstrated file I/O operations
- Implemented user authentication and transaction management
- Practiced defensive programming techniques

## Future Learning Path

This project serves as a bridge between procedural and object-oriented programming, preparing for:
- Refactoring to an object-oriented design
- Implementing more advanced error handling
- Exploring more sophisticated functional programming techniques

## Reflections on Functional Approach

The project showcases how functional programming principles can be applied in C++ to create:
- More predictable code
- Easier testing and debugging
- Clear separation of concerns
- Improved code readability and maintainability

## Getting Started
### Client File Format
Each line in `Clients.txt` follows this structure:
 - AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance

### Login
- Enter Account Number
- Enter PIN Code
- Access main menu with options:
  1. Quick Withdraw
  2. Normal Withdraw
  3. Deposit
  4. Check Balance
  5. Logout
