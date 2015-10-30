#include <array>
#include <vector>
#include <iostream>

#include "gmock\gmock.h"
#include "gtest\gtest.h"

#include "ANN.h"
#include "MinstData.h"

using namespace std;
using namespace CPPANN;

TEST(CharacterRecognition, one_hidden_layer_with_15_neurons)
{
	//Setup ANN
	ANNBuilder<double> ann_builder;
	
	//read raw training material
	MINSTData<double> mINSTData;
	mINSTData.read_data("./MINSTDataset/train-images.idx3-ubyte", "./MINSTDataset/train-labels.idx1-ubyte");

	auto ann = ann_builder.set_layer(0, 28*28)
		.set_layer(1, 15)
		.set_layer(2, 10)
		.build();

	Matrix<double> training_output_data{ 1, 10 };
	for (size_t j = 0; j < 1; j++) {
		for (size_t idx = 0; idx < mINSTData.get_number_of_images(); idx++) {
			auto &training_input_data = mINSTData.get_image(idx);
			auto training_output_data_raw = mINSTData.get_label(idx);

			training_output_data.zero();
			switch (training_output_data_raw) {
			case 0:
				training_output_data(0, 0) = 1.;
				break;
			case 1:
				training_output_data(0, 1) = 1.;
				break;
			case 2:
				training_output_data(0, 2) = 1.;
				break;
			case 3:
				training_output_data(0, 3) = 1.;
				break;
			case 4:
				training_output_data(0, 4) = 1.;
				break;
			case 5:
				training_output_data(0, 5) = 1.;
				break;
			case 6:
				training_output_data(0, 6) = 1.;
				break;
			case 7:
				training_output_data(0, 7) = 1.;
				break;
			case 8:
				training_output_data(0, 8) = 1.;
				break;
			case 9:
				training_output_data(0, 9) = 1.;
				break;
			}

			ann.forward_propagate(training_input_data);
			ann.back_propagate(training_output_data);
		}
		std::cout << "";
	}


		

}