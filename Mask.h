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
        ~Layer() {}

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
        typedef Layer<T>              value_type;
        typedef Layer<T>*             iterator;
        typedef const Layer<T>*       const_iterator;
        typedef Layer<T>&             reference;
        typedef const Layer<T>&       const_reference;
        typedef std::size_t    size_type;

        // Default Constructor
        Layer_System():index(0) {}

        ~Layer_System() {}

        // iterator support
        iterator        begin()       { return _layers; }
        const_iterator  begin() const { return _layers; }
        
        iterator        end()       { return _layers+N; }
        const_iterator  end() const { return _layers+N; }

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

        // operator[]
        reference operator[](size_type i) 
        { 
            return _layers[i];
        }
        
        const_reference operator[](size_type i) const 
        {     
            return _layers[i]; 
        }

        // Size is constant
        static size_type size() { return N; }
        static size_type max_size() { return N; }

        // Get index
        std::size_t get_index() {return index; }

        // Direct access to data (read-only)
        const value_type* data() const { return _layers; }
        value_type* data() { return _layers; }

        // Return pointer to the pos-th layer of the list.
        const_reference data(size_type pos) const {
            if (pos >= index) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
                throw "index out of range";
            }
            return _layers[pos];
        } 
        reference data(size_type pos) {
            if (pos >= index) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
                throw "index out of range";
            }
            return _layers[pos];
        }

        // check range (may be private because it is static)
        static void rangecheck (size_type i) {
            if (i >= size()) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
                throw "index out of range";
            }
        }

        // Layer manipulation
        void add_layer(value_type layer) {
            if (index == N) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
                throw "index out of range";
            }
            _layers[index++] = layer;
        }

        void remove_layer() {
            index--;
        }

        value_type get_top_layer() {
            if (index == 0) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
                throw "index out of range";
            }
            return _layers[index-1];
        }

        // Smooth image for n iterations and stored in CImgList
        /*
            iter is the number of total iterations
        */
        value_type* smooth_layer(value_type layer, const int index, const int iter=50) {
            CImg<T> img = layer.data();
            CImg<T> smooth_img = img.get_smooth(index, iter);
            return new Layer<T>(smooth_img);
        }

        // Blur gradient image
        /*
        * sigma
        */
        value_type* blur_gradient_layer(value_type layer, const double sigma=0) {
            CImg<T> img = layer.data();
            CImg<T> blur_gradient_img = img.get_blur_gradient(sigma);
            return new Layer<T>(blur_gradient_img);
        }

        // Set visibility
        void set_visible(reference layer) {
            if (layer.visible()) {
                return;
            }
            layer.set_visible();
        }

        void set_invisible(reference layer) {
            if (!layer.visible()) {
                return;
            }
            layer.set_invisible();
        }

        // Merge layer
        value_type* merge_layer() {
            if (index == 0) {
                std::out_of_range e("array<>: index out of range");
                //throw exception
                throw "index out of range";
            }
            CImg<T> img = _layers[0].data();
            for (size_type i = 1; i < index; i++) {
                if (_layers[i].visible()) {
                    img = img.draw_image(_layers[i].data());
                }
            }
            return new Layer<T>(img);
        }
    };
}

