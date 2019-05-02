#include "Mask.h"
#ifndef cimg_imagepath
#define cimg_imagepath "img/"
#endif
#undef min
#undef max

using namespace cimg_library;


int main(int argc,char **argv) {
  const CImg<float> image("Lenna.jpg");

  //Test layer
  cimg_extension::Layer<float> layer1(image);
  // img.display("test");

  //Test System
  cimg_extension::Layer_System<float,10> sys;
  cimg_extension::Layer<float> layer2 = *(sys.smooth_layer(layer1, 50, 100)); 


  cimg_extension::Layer<float> layer3 = *(sys.blur_gradient_layer(layer1, 5));

  /* overlap

  CImg<float> l2 = layer2.data();
  CImg<float> l3 = layer3.data();

  l2.draw_image(l3).display();
  l2.save_png("res.png");
  */

  //Test layer manipulation
  sys.add_layer(layer1);
  sys.add_layer(layer2);
  sys.add_layer(layer3);

  /*
  cimg_extension::Layer<float> layer = sys.get_top_layer();
  CImg<float> img = layer.data();
  img.display();
  */

  //Test merge layer
  try {
  	sys.set_invisible(sys.data(-1));
	cimg_extension::Layer<float> layer = *(sys.merge_layer());
	CImg<float> img = layer.data();
	img.display();
  } catch(const char* msg) {
  	std::cerr << msg << std::endl;
  }
  

  return 0;
}

