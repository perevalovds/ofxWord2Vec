# Tools for computing distributed representtion of words

We provide an implementation of the Continuous Bag-of-Words (CBOW) and the Skip-gram model (SG), 
as well as several demo scripts.

Given a text corpus, the word2vec tool learns a vector for every word in the vocabulary using the Continuous
Bag-of-Words or the Skip-Gram neural network architectures. The user should to specify the following:
 - desired vector dimensionality
 - the size of the context window for either the Skip-Gram or the Continuous Bag-of-Words model
 - training algorithm: hierarchical softmax and / or negative sampling
 - threshold for downsampling the frequent words 
 - number of threads to use
 - the format of the output word vector file (text or binary)

Usually, the other hyper-parameters such as the learning rate do not need to be tuned for different training sets. 

The script demo-word.sh downloads a small (100MB) text corpus from the web, and trains a small word vector model. 
After the training is finished, the user can interactively explore the similarity of the words.

## Original code

More information about the scripts is provided at https://code.google.com/p/word2vec/

## Notes on examples

(by perevalovds)

* word-analogy example treats three words typed by user as X - Y + Z.
But, currently it works with normalized input vectors 'M'. It's not ok, 
because (following ofxMSAWord2Vec addon's text my Memo Akten) we must 
combine unnormalized vectors. As a result, it's not so good in combining
vectors (king - man + woman).

So, please see my addon https://github.com/perevalovds/ofxWord2Vec which contains fixed example_analogy.

## Python wrapper
In order to get Python wrapper (https://github.com/danielfrg/word2vec) working 

added word2vec-doc2vec tool support (https://github.com/nliu86/word2vec-doc2vec)

## Hints 
From https://code.google.com/p/word2vec/

The training speed can be significantly improved by using parallel training 
on multiple-CPU machine (use the switch '-threads N'). 
The hyper-parameter choice is crucial for performance (both speed and accuracy), 
however varies for different applications. 
The main choices to make are:

* architecture: skip-gram (slower, better for infrequent words) vs CBOW (fast)
	
* the training algorithm: hierarchical softmax (better for infrequent words) 
	vs negative sampling (better for frequent words, better with low dimensional vectors)
	
* sub-sampling of frequent words: can improve both accuracy and speed for large data sets 
	(useful values are in range 1e-3 to 1e-5)
    
* dimensionality of the word vectors: usually more is better, but not always
    
* context (window) size: for skip-gram usually around 10, for CBOW around 5
	
	
