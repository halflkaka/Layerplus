# Design Documentation
## Layer\<T>
Use a pointer of type CImg\<T> to store a CImg instance of layer. The CImg library provides convenient interface to initialize CImg instance and exception handler, so we don't need to worry about that and we can easily construct the new instance of layer.   
Use a boolean type variable to indicate whether the layer is visible.  
## Layer_System\<T,N>
Use an static array of size N to store layers of type T. We chose to use the low-level array instead of a vector here because we want to simplify our design, which means, we don't consider the case where layers grow dynamically. We simply set a maximum limit on layer number. Since Vector occupies much more memory in exchange for the ability to manage storage and grow dynamically whereas Arrays are memory efficient data structure, so array is accepted.  
## Layer Processing
The specific three layer processing features: Smooth, Blur, Exposure are implemented directly in CImg.h, starts from the line 56148.