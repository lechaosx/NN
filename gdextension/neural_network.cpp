#include "neural_network.h"

#include <feed.h>
#include <activations.h>
#include <serialization.h>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>


NeuralNetwork::NeuralNetwork() {
	if (godot::Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	}
}

bool NeuralNetwork::load_coefficients(const godot::String &path) try {
	std::ifstream stream(path.utf8().get_data());
	
	m_coefficients = deserialize(nlohmann::json::parse(stream));

	m_activations.resize(std::size(m_coefficients));

	for (size_t i = 0; i < std::size(m_activations) - 1; ++i) {
		m_activations[i] = Activations::relu;
	}

	m_activations[std::size(m_activations) - 1] = Activations::softmax;

	emit_signal("network_changed");
	return true;
}
catch (const std::exception &e) {
	godot::print_error("Failed to load coefficients from file", __FUNCTION__, __FILE__, __LINE__);
	return false;
}

godot::TypedArray<float> NeuralNetwork::feed(const godot::TypedArray<float> &inputs) {
	Eigen::VectorXf input_vector(inputs.size());

	for (int i = 0; i < inputs.size(); ++i) {
		input_vector(i) = inputs[i];
	}

	Eigen::MatrixXf outputs = ::feed(zip(m_coefficients, m_activations), input_vector);
	
	godot::TypedArray<float> result {};

	for (int i = 0; i < outputs.rows(); ++i) {
		result.append(outputs(i));
	}

	return result;
}

void NeuralNetwork::_bind_methods() {	
	godot::ClassDB::bind_method(godot::D_METHOD("load_coefficients", "path"), &NeuralNetwork::load_coefficients);
	godot::ClassDB::bind_method(godot::D_METHOD("feed", "inputs"), &NeuralNetwork::feed);

	ADD_SIGNAL(godot::MethodInfo("network_changed"));
}