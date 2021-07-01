#pragma once
#include <string_view>
#include <string>

class Window {
private:
	int width;
	int height;
	std::string title;
public:
	void onResize(int new_width, int new_height);

	int getWidth() const;
	int getHeight() const;
	void setTitle(std::string_view s);
	std::string_view getTitle() const;

	Window();
	virtual ~Window();

};
