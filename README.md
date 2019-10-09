# ofxWord2Vec

ofxWord2Vec is an addon for openframeworks, which implements word2vec word implemented in pure C++, 
with ready-to-use example for computing word arithmetics such as 

* 'king - man + woman'

* 'god - man'

and so on!

It's based on native C Google code:

* https://github.com/perevalovds/word2vec-win32 (forked from zhangyafeikimi/word2vec-win32)

* https://code.google.com/archive/p/word2vec/ 

The addon is inspired by the great addon ofxMSAWord2Vec by Memo Akten, 
but faster and with training implemented on C/C++ (TODO, currently training is on C, but in base_code folder).


## Features

* It uses only openFrameworks; no Python, ML libraries or other addons are required.

* It allows to train and use word embeddings directly from openFrameworks project.

* It works on CPU; it's fast.

* It contains ready to use embedding files, one small for tests and other huge for production, see 'Embeddings files' section below.


## Examples

* example_analogy - it's ready-to-use example which works with words arithmetic.
It allows to find nearest words to the combinations of words separated by ' + '  and ' - ',
such as 'man - animal'. You can use any number of words in equation.

Example is shipped with vec_text8.bin embeddings vectors obtained in the way described in base_code/demo-analogy.sh

## Embeddings files

* Addon's example example_analogy contains embedding file vec_text8.bin (made as described in base_code/demo-analogy.sh).
Words: 71291, dimensions: 200. This file is fast to use and is recommended for fast developing.

* Addon's github Releases tab contains ZIP file with "GoogleNews-vectors-negative300.bin" embedding 
(Mikolov et al's GoogleNews model, https://code.google.com/archive/p/word2vec/). Words: 3 000 000, dimensions: 300.
This is a huge file. It requires 8GB in CPU (because we store original and normalized vectors).
It's works slow, but great.
