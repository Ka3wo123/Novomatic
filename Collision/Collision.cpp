#pragma once
#include "Collision.hpp"

bool isColliding(const triangle& t1, const triangle& t2) {
	const triangle* triangle1 = &t1;
	const triangle* triangle2 = &t2;

	for (int shape = 0; shape < 2; shape++) {
		for (int p = 0; p < 3; p++) {

			vec2 line_r1s = triangle1->points[0];
			vec2 line_r1e = triangle1->points[p];

			for (int q = 0; q < 3; q++) {
				vec2 line_r2s = triangle2->points[q];
				vec2 line_r2e = triangle2->points[(q + 1) % 3];

				float h = (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r1e.y) - (line_r1s.x - line_r1e.x) * (line_r2e.y - line_r2s.y);
				float t1 = ((line_r2s.y - line_r2e.y) * (line_r1s.x - line_r2s.x) + (line_r2e.x - line_r2s.x) * (line_r1s.y - line_r2s.y)) / h;
				float t2 = ((line_r1s.y - line_r1e.y) * (line_r1s.x - line_r2s.x) + (line_r1e.x - line_r1s.x) * (line_r1s.y - line_r2s.y)) / h;

				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f) {
					return true;
				}
			}
		}


	}

	return false;

}


