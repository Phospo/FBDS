# Copilot Custom Instructions

## Rule: Polish class documentation comments
- For every new C++ class in this repository, include Polish comments at:
  - class-level (`/** ... */` above the class declaration)
  - `private:` section (if present) with per-field or per-subgroup comment block style
  - `public:` section with method/constructor comments as in existing files (`cconnection.h`, `coutput.h`, `cfunctionblock.h`)
- Follow `CFunctionBlock` style exactly:
  - Top-of-class comment: `/** CClassName\n\n    Reprezentacja ...\n*/`
  - All method comments in Polish and with `@param`/`@return` tags where appropriate.
  - Code semantics in comments, no English.
- Enforcement: PRs should be reviewed for this in every new class header and updates to existing classes. If comments change in any existing class header, Polish-style comments must still be preserved and updated accordingly.
- If a user request is to update comments in an existing file, the assistant MUST apply these same rules instead of ignoring them.

## Rule: FBD simulator architecture
- Object-oriented design and polymorphism must be used for connections, block inputs, block outputs, and transmitted values.
- New block types should be implemented via inheritance and polymorphism, with consistent encapsulation.
- Interface-based architecture must be applied for:
  - Function blocks
  - Inputs
  - Outputs
  - Connections
- Container, Engine, and Builder classes should use generic interfaces (polymorphic pointers/references).
- Simulation cycle must be strict and step-by-step: each block in each step must read inputs, calculate, and update outputs.
- Data and error propagation rules:
  - output status signals errors when input connection is missing, invalid operation, or bad input status
  - missing input or invalid signals should not be silently ignored
  - timestamp propagation for incoming inputs is ignored by default unless explicitly required by a block type
- Configuration must be local and text-based; parser for FBD setups should be implemented in `CFBDBuilder` (or equivalent) and use manual text files.
- For any requested feature extension or behavioral change not explicitly defined by the existing rules, ask the user for confirmation before implementing.

## Examples
### New class
```cpp
/** CMyNewClass

    Reprezentacja ... w schemacie FBD
*/
class CMyNewClass {
  unsigned FValue{0};

public:
  /**
      Konstruktor podstawowy

      @param _value Wartość początkowa
  */
  CMyNewClass(unsigned _value);

  /**
      Pobranie wartości

      @return aktualna wartość
  */
  unsigned getValue() const;
};
```

### Update existing class
```cpp
/** COutput

    Reprezentacja wyjścia bloku funkcyjnego
*/
class COutput {
    unsigned FNumber{0};
    SDataSample FValue;

public:
    /**
        Konstruktor podstawowy

        @param _number Numer wyjścia
    */
    COutput(unsigned _number);

    /**
        Pobranie aktualnej wartości wyjścia.

        @return Próbka danych
    */
    SDataSample getData() const;

    /**
        Ustawienie aktualnej wartości wyjścia.

        @param _val Nowa próbka danych
    */
    void setData(const SDataSample& _val);
};
```

