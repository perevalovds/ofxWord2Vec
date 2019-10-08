# ofxWord2Vec

ofxWord2Vec is an openFrameworks addon for working with word2vec embedding.

It's based on native C Google code:

* https://github.com/perevalovds/word2vec-win32 (forked from zhangyafeikimi/word2vec-win32)

* https://code.google.com/archive/p/word2vec/ 

The addon is inspired by the great addon ofxMSAWord2Vec by Memo Akten, 
but implemented on pure C/C++.


## Features

* It uses only openFrameworks; no Python, ML libraries or other addons are required.

* It allows to train and use word embeddings directly from openFrameworks project.

* It works on CPU; it's fast.


## Examples

* example_analogy - it's ready-to-use example which works with words arithmetic.
It allows to find nearest words to the combinations of words separated by ' + '  and ' - ',
such as 'man - animal'. You can use any number of words in equation.

Example shipped with vec_text8.bin embeddings vectors obtained in the way described in original_code/demo-analogy.sh

