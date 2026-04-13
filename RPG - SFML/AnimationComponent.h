#pragma once

class AnimationComponent
{
private:
	class Animation {
	public:

		//Variables
		sf::Sprite& sprite;
		sf::Texture& texturSheets;
		float animationTime;
		float timer;
		int width;
		int hight;
		sf::IntRect begin;		//start
		sf::IntRect end;		//end
		sf::IntRect current;	//current image
		int priority;
		bool done;


		//constructors
		Animation(sf::Sprite& sprite, sf::Texture& texturSheets,
			int startFrame_x, int startFrame_y, int frames_x, int frames_y,
			int width, int hight, float speed, int priority);

		//Function
		void play(const float& dt, float modPrecent);
		void pause();
		void restart();
	};


	//Variables
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animation;
	Animation* currentAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture);
	virtual ~AnimationComponent();

	//Accessors
	bool isDone(const std::string key);

	//Methods
	void addAnimtion(const std::string key, int startFrame_x, int startFrame_y, int frames_x, int frames_y,
		int width, int hight, float speed, int priority = 0);

	void play(const std::string key, const float& dt, const float& modifier = 1, const float& modifierMax = 1);//Cover function
	void play(const std::string key, bool forcePlayTillEnd, const float& dt, const float& modifier = 1, const float& modifierMax = 1);

	//דרך יותר נכונה לבנות את כל זה, לעשות עידכון, ואז כשעושים הפעל זה רק בודק האם להחליף לחדש או לא.
	// בעידכון אמור להיות שהוא מנגן כל הזמן, במידה והוא מקבל כל הזמן ערכים הוא בוחר מי מבניהם לנגן ולפי זה.
	// למשל: מצב רגיל הדמות עומדת, נכנס התקפה, יש קדימות, אז מחליף את המפתח לזה, נגמרה ההתקפה, ינגן את מה שעכשיו יכנס, שאצל השחקן זה אמור להיות לעמוד
	// 
	//void update(const float& dt);
};

