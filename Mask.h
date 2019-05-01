/*
    #   File        :   Mask.h
    #   Description :   Extension to C++ Template Image Processing Library CImg.h
                        Mask Manipulation Toolkit
*/
#include "CImg.h"

namespace mask {
    template<typename T>
    class Layer {
        CImg<T> *_data;
        bool _is_visible;
    public:

        //  Default deconstructor
        ~Layer() {
            delete[] _data;
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
            _data = new CImg(img);
            _is_visible = true;
        }

        Layer(const CImg<T> &img, const bool is_visible): _is_visible(true)
        {
            _data = new CImg(img);
            _is_visible = is_visible;
        }

        // Visibility
        bool visible() {
            return this._is_visible;
        }

        void set_visible() {
            _is_visible = true;
        }

        void set_invisible() {
            _is_visible = false;
        }

        // Data
        CImg<T>* data() {
            return _data;
        }
    };

    template<typename T>
    class Mask_System {
        vector<Layer<T>> _layers;
    public:
        // type definitions
        typedef T value_type;

        // Default Constructor
        Mask_System(): _layers(0){}

        // Add layer
        void add_layer(Layer<T> layer) {
            _layers.push_back(layer);
        }

        // Remove last layer
        void remove_layer() {
            _layers.pop_back();
        }

        // Smooth image for n iterations and stored in CImgList
        /*
            iter is the number of total iterations
        */
        Layer<T> smooth_layer(Layer<T> layer, const int index, const int iter=50) {
            CImg<T> img = layer._data;
            CImg<T> smooth_img = img.get_smooth(index, iter);
            return new Layer<T>(smooth_img);
        }

        // Blur gradient image
        /*
        * sigma
        */
        Layer<T> blur_gradient_layer(Layer<T> layer, const double sigma=0) {
            CImg<T> img = layer._data;
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
    }
}

