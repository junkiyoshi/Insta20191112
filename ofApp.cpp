#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->ico_sphere = ofIcoSpherePrimitive(125, 4);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh_list.clear();
	auto triangle_list = this->ico_sphere.getMesh().getUniqueFaces();

	vector<glm::vec3> locations{ glm::vec3(-300, -300, 0), glm::vec3(0, -300, 0), glm::vec3(300, -300, 0),
		glm::vec3(-300, 0, 0), glm::vec3(0, 0, 0), glm::vec3(300, 0, 0), 
		glm::vec3(-300, 300, 0), glm::vec3(0, 300, 0), glm::vec3(300, 300, 0)};
	
	for (auto& triangle : triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		int noise_value = ofMap(ofNoise(avg.x * 0.005, avg.y * 0.005, avg.z * 0.005, ofGetFrameNum() * 0.01), 0, 1, 0, locations.size());

		ofMesh mesh;

		mesh.addVertex(locations[noise_value] + triangle.getVertex(0));
		mesh.addVertex(locations[noise_value] + triangle.getVertex(1));
		mesh.addVertex(locations[noise_value] + triangle.getVertex(2));
		
		mesh.addIndex(0);
		mesh.addIndex(1);
		mesh.addIndex(2);

		this->mesh_list.push_back(mesh);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	for (auto& mesh : this->mesh_list) {

		ofSetColor(239);
		mesh.drawFaces();

		ofSetColor(39);
		mesh.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}