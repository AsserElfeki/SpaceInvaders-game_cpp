module; 

export module ScoreHandler;

export class ScoreHandler
{
private: 
	int current_score = 0;
	int last_level_score= 0;

public: 

	void setScore(int _score) { current_score = _score; }
	
	int getScore() { return current_score; }

	void increaseScoreWithTime(float time) { current_score += (time * 60); }

	void increaseScoreWhenHitAlien() { current_score += 100; }

	void decreaseScoreWhenHealthDecreased() { current_score -= 300; }
	
	void setLastLevelScore(int score) {last_level_score = score;}
	
	int lastLevelScore() { return last_level_score; }

	void resetScores() {
		current_score = 0;
		last_level_score = 0;
	}
};