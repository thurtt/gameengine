/*
 *  sprite.cpp
 *  gltest
 *
 *  Created by Stuart Templeton on 1/8/11.
 *  Copyright 2011 none. All rights reserved.
 *
 */

#include "sprite.h"
#include "SOIL.h"

vector< pair<const char*, GLuint> > master_texture_list;

game_sprite::game_sprite(){
	xy(10, 10);
	wh(10, 10);
	_blockMovement = false;
	_blockVisibility = false;
	texture = LoadTexture("img.png");
	textures.push_back( texture );
	includeAnimation(ANIM_NONE, texture);
	_angle = 0.0f;
	use_los = false;
}

game_sprite::game_sprite(float _x_, float _y_, float _width_, float _height_, const char * _filename, bool vis, bool mov){
	xy(_x_, _y_);
	wh(_width_, _height_);
	texture_file = _filename;
	_blockMovement = mov;
	_blockVisibility = vis;
	
	texture = LoadTexture(texture_file);
	textures.push_back( texture );
	includeAnimation(ANIM_NONE, texture);
	_angle = 0.0f;
	use_los = false;
}

void game_sprite::includeAnimation(int anim, char * t){
	animations[anim] = LoadTexture(t);
}

void game_sprite::includeAnimation(int anim, GLuint t){
	animations[anim] = t;
}

void game_sprite::useAnimation(int anim){
	if (animations.find(anim) != animations.end() ){
		texture = animations[anim];
	}else{
		texture = 1;
	}
	
	//STARTUP for different animation things.
	frame = 0;
	
	switch (texture) {
		case ANIM_NONE:
			break;
		case ANIM_IDLE:
			break;
		case ANIM_WALK:
			break;
		case ANIM_RUN:
			break;
		case ANIM_ACTIVATE:
			break;
		case ANIM_HIDE:
			break;
		case ANIM_EXPLODE:
			break;
		case ANIM_AMBIENT:
			// to make the ambience seem real, rand frame
			srand( time(NULL) );
			frame = rand() % ANIM_MAX_FRAMES;
			break;
		default:
			break;
	}
}

void game_sprite::animate(){
	frame++;
	if (frame >=ANIM_MAX_FRAMES ) frame = 0;

	switch (texture) {
		case ANIM_NONE:
			//refuse animation here.
			frame = 0;
			break;
		case ANIM_IDLE:
			break;
		case ANIM_WALK:
			break;
		case ANIM_RUN:
			break;
		case ANIM_ACTIVATE:
			break;
		case ANIM_HIDE:
			break;
		case ANIM_EXPLODE:
			break;
		case ANIM_AMBIENT:
			break;
		default:
			break;
	}
}

void game_sprite::xy(float _x_, float _y_){
	_x = _x_;
	_y = _y_;
	move_up = 0;
	move_down = 0;
	move_left = 0;
	move_right = 0;
}

void game_sprite::wh(float _width_, float _height_){
	height = _height_;
	width = _width_;
}

game_sprite::~game_sprite(){
	int i;
	for (i = 0; i < textures.size(); i++){
		glDeleteTextures( 1, &textures[i] );
	}
	animations.clear();
}

bool game_sprite::blockVisibility(){
	return _blockVisibility;
}
void game_sprite::blockVisibility(bool v){
	_blockVisibility = v;
}
bool game_sprite::blockMovement(){
	return _blockMovement;
}
void game_sprite::blockMovement(bool v){
	_blockMovement = v;
}


void game_sprite::text(char *str){
	renderSpacedBitmapString(_x + height /2,_y + width/2,0, GLUT_BITMAP_8_BY_13,str);
}

void game_sprite::renderSpacedBitmapString(float x,float y,int spacing,void *font,char *str) {
	
	char *c;
	int x1=x;
	
	for (c=str; *c != '\0'; c++) {
		glColor3f(1.0, 0.3, 0.3);
		glRasterPos2f(x1,y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font,*c) + spacing;
	}
}

void game_sprite::draw(){
	draw(0.0f, 0.0f);
}

void game_sprite::draw(float offset_x, float offset_y){

	
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBindTexture( GL_TEXTURE_2D, texture );
	
	// not exactly sure how this works, but it does.
	// use the _angle member variable to change the
	// direction of the sprite.
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5,0.5,0.0);
	glRotatef(_angle,0.0,0.0,1.0);
	glTranslatef(-0.5,-0.5,0.0);
	glMatrixMode(GL_MODELVIEW);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	

	glPushMatrix();
	float translated_x;
	float translated_x2;
	
	if (texture == animations[ANIM_NONE]) {
		translated_x = 0;
		translated_x2 = 1;
	}else {
		translated_x = ((float)frame * (float)width)/(ANIM_MAX_FRAMES * (float)width);
		translated_x2 = (((float)frame + 1) * (float)width)/(ANIM_MAX_FRAMES * (float)width);
	}

	glBegin(GL_QUADS);
	glColor4f(1.0f,1.0f,1.0f,1.0f);			// Full Brightness, 0.5f == 50% Alpha ( NEW )
	glTexCoord2d(translated_x,0.0f);	glVertex2f( _x + 0.0f + offset_x ,  _y + 0.0f + offset_y );
    glTexCoord2d(translated_x2,0.0f);	glVertex2f( _x + width + offset_x , _y +   0.0f + offset_y );
    glTexCoord2d(translated_x2, 1.0f);	glVertex2f( _x + width + offset_x , _y + height + offset_y );
    glTexCoord2d(translated_x, 1.0f);	glVertex2f( _x +  0.0f + offset_x , _y + height + offset_y );
	
	glEnd();
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	if ( use_los ) 
	{
		// find the eyeballs
		// lets say they're in the center of the sprite
		
		float eye_x = (_x + offset_x) + (width / 2);
		float eye_y = (_y + offset_y) + (height / 2);
		// draw our fov
		draw_fov( eye_x, eye_y );
	}
	/*char str [100];
	sprintf(str, "%f,%f", _x + offset_x + width, _y + offset_y + height);
	text(str);*/
}

GLuint game_sprite::LoadTexture( const char * filename){
	
	GLuint _texture;
	int i;
	for (i = 0; i < master_texture_list.size(); i++){
		if (strcmp(master_texture_list[i].first, filename) == 0){
			return master_texture_list[i].second;
		}
	}
	_texture = SOIL_load_OGL_texture
			(
			 filename,
			 SOIL_LOAD_AUTO,
			 SOIL_CREATE_NEW_ID,
			 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			 );
	master_texture_list.push_back(make_pair(filename, _texture));
	return _texture;
}

void game_sprite::draw_fov( float ref_x, float ref_y )
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(ref_x,ref_y,0.0);	// <- the translation used was world x,y, so it was rotating around screen 0,0
	glRotatef(-_angle,0.0,0.0,1.0); // technically, you have to rotate this opposite to make it appear right.
	glTranslatef(-ref_x, -ref_y, -0.0);

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f,0.0f,0.0f,0.5f);			// Full Brightness, 0.5f == 50% Alpha ( NEW )
	
	glVertex2f(ref_x, ref_y);			// first corner
	glVertex2f(ref_x - ( FIELD_OF_VISION / 2), ref_y + DEPTH_OF_VISION );	// second corner
	glVertex2f(ref_x + ( FIELD_OF_VISION / 2), ref_y + DEPTH_OF_VISION );	// third corner
	glEnd();
	glPopMatrix();

}

void game_sprite::movement(){
	float delta = 0.8;
	//texture = 1;
	if ((move_right > 0) || (move_left > 0) || (move_up > 0) || (move_down > 0)){
		if (texture != animations[ANIM_WALK]) {
			useAnimation(ANIM_WALK);
		}
	}
	
	if (move_right > 0)	{ 
		_x += delta; 
		_angle = 90;
	}
	if (move_left > 0)	{ 
		_x -= delta;
		_angle = 270;
	}
	if (move_up > 0)	{ 
		_y += delta;
		_angle = 0;
	}
	if (move_down > 0)	{ 
		_y -= delta; 
		_angle = 180;
	}
}
