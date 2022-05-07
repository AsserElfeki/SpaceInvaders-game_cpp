module; 

export module ScoreHandler;

export class ScoreHandler
{
private: 
	int current_score = 0;
	int last_level_score= 0;

public: 

	void set_Score(int _score) { current_score = _score; }
	
	int get_Score() { return current_score; }

	void increase_Score_With_Time(float time) { current_score += (time * 60); }

	void increase_Score_When_Hit_Alien() { current_score += 100; }

	void decrease_Score_When_Health_Decreased() { current_score -= 300; }
	
	void setLastLevelScore(int score) {
		last_level_score = score;
	}
	
	int lastLevelScore() { return last_level_score; }

	void reset_scores() {
		current_score = 0;
		last_level_score = 0;
	}
};