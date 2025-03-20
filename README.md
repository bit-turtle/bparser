# bparser
A simple parser that parses many file formats to a single tree structure
## bparser::node structure
All parsed files become `bparser::node` trees.
Each node consists of a `std::string` value and a `std::vector` of subnodes.
The root node has a value of the filename.
### Planned encoding support
I plan to support many tree style text based encodings (With all values being treated as strings) such as:
* CSV (Comma Separated Values) *Each subnode from the root would be a row*
* S-Expressions *The first item in an S-Expression would be the value*
* UCL (Universal Configuration Language) *Seems very compatible with the structure*
* JSON *Items with no name would have an empty value*
