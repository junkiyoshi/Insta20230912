#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	if ((ofGetFrameNum() % 60 > 15 && ofGetFrameNum() % 60 < 30) || (ofGetFrameNum() % 60 > 45 && ofGetFrameNum() % 60 < 60)) {

		this->noise_param += 0.1;
	}

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 2;
	float theta_deg_step = 2;
	float threshold = 0.5;

	float R = 250;
	float base_r = R * 0.25;
	float r;

	if (ofGetFrameNum() % 60 < 30) {

		if (ofGetFrameNum() % 60 < 15) {

			r = R * 0.25;
		}
		else {

			r = ofMap(ofGetFrameNum() % 60, 15, 30, R * 0.25, R * 0.35);
		}
	}
	else {

		if (ofGetFrameNum() % 60 < 45) {

			r = R * 0.35;
		}
		else {

			r = ofMap(ofGetFrameNum() % 60, 45, 60, R * 0.35, R * 0.25);
		}
	}

	ofColor face_color = ofColor(39, 39, 239);
	ofColor line_color = ofColor(39);

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg) * 0.03, this->noise_param));
			if (noise_value <= threshold) { continue; }

			auto noise_1 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg - theta_deg_step, phi_deg) * 0.03, this->noise_param));
			auto noise_2 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg + phi_deg_step) * 0.03, this->noise_param));
			auto noise_3 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg - phi_deg_step) * 0.03, this->noise_param));
			auto noise_4 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg + theta_deg_step, phi_deg) * 0.03, this->noise_param));

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

			this->face.addVertices(vertices);

			this->face.addColor(face_color);
			this->face.addColor(face_color);
			this->face.addColor(face_color);
			this->face.addColor(face_color);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			if (noise_1 <= threshold) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[2]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_2 <= threshold) {

				this->line.addVertex(vertices[2]);
				this->line.addVertex(vertices[3]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_3 <= threshold) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[1]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_4 <= threshold) {

				this->line.addVertex(vertices[1]);
				this->line.addVertex(vertices[3]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);


			}
		}
	}

	if (ofGetFrameNum() % 60 < 30) {

		if (ofGetFrameNum() % 60 < 15) {

			r = R * 0.35;
		}
		else {

			r = ofMap(ofGetFrameNum() % 60, 15, 30, R * 0.35, R * 0.25);
		}
	}
	else {

		if (ofGetFrameNum() % 60 < 45) {

			r = R * 0.25;
		}
		else {

			r = ofMap(ofGetFrameNum() % 60, 45, 60, R * 0.25, R * 0.35);
		}
	}


	face_color = ofColor(239, 39, 39);
	line_color = ofColor(39);

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg) * 0.03, this->noise_param));
			if (noise_value >= threshold) { continue; }

			auto noise_1 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg - theta_deg_step, phi_deg) * 0.03, this->noise_param));
			auto noise_2 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg + phi_deg_step) * 0.03, this->noise_param));
			auto noise_3 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg - phi_deg_step) * 0.03, this->noise_param));
			auto noise_4 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg + theta_deg_step, phi_deg) * 0.03, this->noise_param));

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

			this->face.addVertices(vertices);

			this->face.addColor(face_color);
			this->face.addColor(face_color);
			this->face.addColor(face_color);
			this->face.addColor(face_color);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			if (noise_1 >= threshold) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[2]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_2 >= threshold) {

				this->line.addVertex(vertices[2]);
				this->line.addVertex(vertices[3]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_3 >= threshold) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[1]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_4 >= threshold) {

				this->line.addVertex(vertices[1]);
				this->line.addVertex(vertices[3]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);


			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	int R = 250;
	int r = R * 0.3;

	this->cam.begin();
	ofRotateX(90);
	this->cam.setPosition(R, 0, r * 2);
	ofRotateZ(ofGetFrameNum() * 2.4);

	this->line.draw();
	this->face.draw();


	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}