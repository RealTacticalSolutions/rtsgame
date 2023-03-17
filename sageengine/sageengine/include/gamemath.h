#pragma once

/***************************************************************************
								GAME MATH CLASS
***************************************************************************/

/**
*	This class holds most of the math necesaary for creating 2d and 3d applications
*/


static class GameMath {

private:


public:

	/**
	*	@brief a static function that calculates a position in world space from screen/window space
	* 
	*	@param windowPosition A vec2 that holds the position on the window to convert
	*	@param windowSize A vec2 holding the size of the window so the windowPosition can be interpolated;
	*	@param camera A camera that holds informmation like position and aspect ratio necessary for correct calculations
	* 
	*	@returns A vec3 that holds the converted world position in 3d
	*/
	static glm::vec3 windowToWorldPos(glm::vec2 windowPosition,glm::vec2 windowSize ,Camera camera);

};