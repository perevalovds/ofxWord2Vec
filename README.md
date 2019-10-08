# ofxWord2Vec

ofxWord2Vec is an openFrameworks addon for working with word2vec embedding.

It's based on native C Google code:

* https://github.com/perevalovds/word2vec-win32 (forked from zhangyafeikimi/word2vec-win32)

* https://code.google.com/archive/p/word2vec/ 

The addon is inspired by the great addon ofxMSAWord2Vec by Memo Akten, 
but implemented on pure C/C++.



## Features:

* It uses only openFrameworks; no Python or any ML libraries.

* It works very fast.

* It allows to train and work with word embeddings from openFrameworks.

## Examples

* example_analogy - this example loads binary word vectors and allows
to compute X - Y + Z = ?
It uses vec_text8.bin embeddings vectors obtained in the way as described in original_code/demo-analogy.sh
