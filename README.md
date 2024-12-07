# ATM Banking System

## Overview

This ATM banking system project was developed as a self-learning initiative to explore C++ programming concepts and software design principles. The primary goal was to create a fully functional application, with an emphasis on writing clean, maintainable code while applying functional programming concepts.

## Features

- User Authentication
- Transaction Management
  - Quick Withdraw
  - Normal Withdraw
  - Deposit
  - Balance Inquiry
- File-based Data Persistence
- Modular Function Design
    
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
     
## Technical Skills Demonstrated

- Procedural Programming
- File I/O Operations
- Data Management
- Console Application Development
- Error Handling

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
