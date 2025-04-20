# Variables and Mutability
## Variables
#### Decleration
Use `let` to bind a value to a variable. By default, variables are immutable.

```rust
let x = 5; // Immutable
```

#### Type Inferences
Rust infers types, but you can annotate explicitly.
```rust
let y: i32 = 10; // Explicit type (i32 = 32-bit integer)
```

#### Variable Scope
Just like in C/C++, variables live only in their block `{}`.
```rust
{
    let inner = 42; // Only exists here
}

println!("{inner}"); // Error: `inner` is out of scope
```

## Mutability
#### Mutable Variable
Prevents accidental changes (safer concurrency). The compiler optimizes immutable variables better. Add `mut` to make a variable mutable.
```rust
let mut z = 15; // Mutable (can change `z` later)
z = 20;         // Allowed
```

#### Mutable Rules
One mutable reference at a time.
```rust
let mut s = String::from("hello");
let r1 = &mut s; // First mutable borrow
let r2 = &mut s; // Error: cannot borrow `s` as mutable twice
```

Immutable references are unlimited.
```rust
let t = String::from("world");
let tr1 = &t; // Allowed
let tr2 = &t; // Also allowed
```

## Constants
Use `const` for compile-time constants (must annotate type).
```rust
const MAX_POINTS: u32 = 100_000; // Uppercase naming convention
```
Constants are always immutable and inlined at compile time.

## Shadowing
Redeclare a variable with the same name (creates a new binding).
```rust
let a = 5;
let a = a + 1; // Shadowing (new `a` = 6)
```

Allows changing type (unlike `mut`).
```rust
let b = "hello";
let b = b.len(); // Changes from `&str` to `usize`
```

## Example
```rust
fn main() 
{
    let immutable = 10;       // Immutable
    let mut mutable = 20;     // Mutable
    mutable += 1;             // Allowed

    let shadowed = "text";    // &str
    let shadowed = shadowed.len(); // usize (shadowing)

    const PI: f64 = 3.14;     // Constant
}
```