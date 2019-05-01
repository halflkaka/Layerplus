/*
    #   File        :   Mask.h
    #   Description :   Extension to C++ Template Image Processing Library CImg.h
                        Mask Manipulation Toolkit
*/
#include "CImg.h"
using namespace cimg_library;

namespace cimg_extension {
    template<typename T>
    class Layer {
        CImg<T> *_data;
        bool _is_visible;
    public:

        //  Default deconstructor
        ~Layer() {
        }

        // type definitions
        typedef T              value_type;
        typedef T*             iterator;
        typedef const T*       const_iterator;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef std::size_t    size_type;

        //  Default constructor
        /**
         * Construct a new empty layer instance
        **/
        Layer(): _data(0), _is_visible(true){}

        //  Construct layer of specific image
        /**
         * \param img CImg instance
        **/
        Layer(const CImg<T>& img) {
            _data = new CImg<T>(img);
            _is_visible = true;
        }

        Layer(const CImg<T> &img, const bool is_visible): _is_visible(true)
        {
            _data = new CImg<T>(img);
            _is_visible = is_visible;
        }

        // Visibility
        bool visible() {
            return _is_visible;
        }

        void set_visible() {
            _is_visible = true;
        }

        void set_invisible() {
            _is_visible = false;
        }

        // Data
        CImg<T> data() {
            return *_data;
        }
    };

    template<typename T, std::size_t N>
    class Layer_System {
        Layer<T> _layers[N];
        std::size_t index;
        unsigned int _width, _allocated_width;
    public:
        // type definitions
        typedef T              value_type;
        typedef Layer<T>*             iterator;
        typedef const Layer<T>*       const_iterator;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef std::size_t    size_type;

        // Default Constructor
        Layer_System():index(0) {}

        ~Layer_System() {
            // delete[] _layers;
        }

        //! Destructor \inplace.
        Layer_System<T,N>& assign() {
          delete[] _layers;
          _width = _allocated_width = 0;
          _layers = 0;
          return *this;
        }

        Layer_System<T,N>& clear() {
          return assign();
        }

        //! Return a reference to an empty list.
        /**
          \note Can be used to define default values in a function taking a CImgList<T> as an argument.
          \code
          void f(const CImgList<char>& list=CImgList<char>::empty());
          \endcode
        **/
        static Layer_System<T,N>& empty() {
          static Layer_System<T,N> _empty;
          return _empty.assign();
        }

        //! Return a reference to an empty list \const.
        static const Layer_System<T,N>& const_empty() {
          static const Layer_System<T,N> _empty;
          return _empty;
        }

        // at() with range check
        reference at(size_type i) { rangecheck(i); return _layers[i]; }
        const_reference at(size_type i) const { rangecheck(i); return _layers[i]; }
    
        // front() and back()
        reference front() 
        { 
            return _layers[0]; 
        }
        
        const_reference front() const 
        {
            return _layers[0];
        }
        
        reference back() 
        { 
            return _layers[N-1]; 
        }
        
        const_reference back() const 
        { 
            return _layers[N-1]; 
        }

        // size is constant
        static size_type size() { return N; }
        static size_type max_size() { return N; }

        // get index
        std::size_t get_index() {return index; }

        // direct access to data (read-only)
        const T* data() const { return _layers; }
        T* data() { return _layers; }

        // check range (may be private because it is static)
        static void rangecheck (size_type i) {
            if (i >= size()) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
            }
        }

        // Layer manipulation
        void add_layer(Layer<T> layer) {
            if (index == N) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
            }
            _layers[index++] = layer;
        }

        void remove_layer() {
            index--;
        }

        Layer<T> get_top_layer() {
            if (index == 0) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
            }
            return _layers[index-1];
        }

        // Smooth image for n iterations and stored in CImgList
        /*
            iter is the number of total iterations
        */
        Layer<T>* smooth_layer(Layer<T> layer, const int index, const int iter=50) {
            CImg<T> img = layer.data();
            CImg<T> smooth_img = img.get_smooth(index, iter);
            return new Layer<T>(smooth_img);
        }

        // Blur gradient image
        /*
        * sigma
        */
        Layer<T>* blur_gradient_layer(Layer<T> layer, const double sigma=0) {
            CImg<T> img = layer.data();
            CImg<T> blur_gradient_img = img.get_blur_gradient(sigma);
            return new Layer<T>(blur_gradient_img);
        }

        // Set visibility
        void set_visible(Layer<T> layer) {
            if (layer.visible()) {
                return;
            }
            layer.set_visible();
        }

        void set_invisible(Layer<T> layer) {
            if (!layer.visible()) {
                return;
            }
            layer.set_invisible();
        }
    };
}

