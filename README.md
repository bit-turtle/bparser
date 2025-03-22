# bparser
A simple single-pass parser that parses and encodes many file formats to a simple tree structure with all values being treated as strings.
## bparser::node structure
All parsed files become `bparser::node` trees.
Each node consists of a `std::string` value and a `std::vector` of subnodes.
## Using the library
Parse and encode files using the `parse` and `encode` functions in the namespaces of each encoding.  
Parse Function Signature: `bparser::node& parse(std::istream& file)`  
Encode Function Signature: `void encode(bparser::node& node, std::istream& file)`
## Supported encodings
* CSV `bparser::csv` (Each subnode from the root is a row)
  - Root node value: "csv"
  - Root subnode values: "row"
* S-Expressions `bparser::sexpr` (Each subnode from the root is a separate S-Expression)
  - Root node value: "sexpr"
  - Default value: "" (Empty String)
  - First item in the S-Expression is the value
  - Values following the first are in subnodes
  - The entire file is treated as an S-Expression
* TSV `bparser::tsv` (Each subnode from the root is a row)
  - Root node value: "tsv"
  - Root subnode values: "row"
### Planned encoding support
I plan to support many tree style text based encodings (With all values being treated as strings) such as:
* UCL (Universal Configuration Language) *Seems very compatible with the structure*
* JSON *Items with no name would have an empty value*
