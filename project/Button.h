#pragma once

class Button
{
	/*
	* This wrapper class contains rectangle shape and text
	* both will be rendered at same location to form a button representation
	*/
protected:
	sf::RectangleShape button;
	sf::Font m_font;
	sf::Text text;
	std::string m_name;
	sf::Vector2f button_position;
	sf::Vector2f text_position;
public:
	Button()
	{
		//Fixed attribute
		button.setFillColor(sf::Color::White);
		button.setSize(sf::Vector2f(120,30));
		if (!m_font.loadFromFile("Font/calibri-regular.ttf"))
			std::cout << "Error: Failed to load font! " << std::endl;
		text.setFont(m_font);
		text.setCharacterSize(20);
		text.setFillColor(sf::Color::Black);
	}
	~Button()
	{
	}
	void setName(const std::string& name)
	{
		m_name = name;
	}
	std::string getName()
	{
		return m_name;
	}
	void setPosition(sf::Vector2f pos)
	{
		button_position = pos;
	}
	void updateButton()
	{
		int offset = 3;
		if (m_name.length() < 12)
			offset = m_name.length();
		if (m_name.length() > 15)
			button.setSize(sf::Vector2f(185, 30));
		//Variable attribute
		button.setPosition(button_position);
		text.setPosition(button_position.x+offset, button_position.y);
		text.setString(m_name);
		//std::cout << m_name << " " << text.findCharacterPos(14).x << std::endl;
	}
	void renderButton(sf::RenderTarget& target)
	{
		target.draw(button);
		target.draw(text);
	}
	bool isPressed(const sf::Vector2f& mousePOS)
	{
		if (button.getGlobalBounds().contains(mousePOS))
			return true;
		else
			return false;
	}
};

