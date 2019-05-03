#include "Layer.h"
#ifndef cimg_imagepath
#define cimg_imagepath "img/"
#endif
#undef min
#undef max

using namespace cimg_library;


int main() {
  CImg<float> image("Lenna.jpg");
  CImg<float> img1("overlay.jpg");
  CImg<float> img2("gradient.jpg");

  //Test layer
  cimg_extension::Layer<float> layer1(image);

  //Test System
  cimg_extension::Layer_System<float,10> sys;
  // cimg_extension::Layer<float> layer2 = *(sys.smooth_layer(layer1, 150, 200)); 
  cimg_extension::Layer<float> layer3 = *(sys.blur_gradient_layer(layer1, 5));
  layer3.data().display();
  cimg_extension::Layer<float> layer4 = *(sys.exposure_layer(layer1, 0.5));
  cimg_extension::Layer<float> layer5(img1);
  cimg_extension::Layer<float> layer6(img2);

  /* overlap

  CImg<float> l2 = layer2.data();
  CImg<float> l3 = layer3.data();

  l2.draw_image(l3).display();
  l2.save_png("res.png");
  */

  //Test layer manipulation
  // sys.add_layer(layer1);
  // sys.add_layer(layer2);
  sys.add_layer(layer3);
  // sys.add_layer(layer4);
  sys.add_layer(layer6);
  sys.add_layer(layer5);

  /*
  cimg_extension::Layer<float> layer = sys.get_top_layer();
  layer.data().display();
  */

  //Test merge layer
  try {
  	sys.set_invisible(sys.data(1));
  	cimg_extension::Layer<float> layer = *(sys.merge_layer());
  	CImg<float> img = layer.data();
  	img.display();
  } catch(const char* msg) {
  	std::cerr << msg << std::endl;
  }
  

  return 0;
}

