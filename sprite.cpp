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
#include "collision.h"
#include "tiles.h"
#include "rotation.h"
#include <math.h>


vector< pair<const char*, GLuint> > master_texture_list;

game_sprite::game_sprite()
{
	generalInit(10, 10, 10, 10, "img_png");
	attr->setAttribute(BLOCK_MOVEMENT, 0);
	attr->setAttribute(BLOCK_VISIBILITY, 0);
}

game_sprite::game_sprite(float _x_, float _y_, _sprite_data * sd)
{
	generalInit( sd->x + _x_, sd->y + _y_, sd->width, sd->height, sd->texture );
	attr->setAttribute(SPAWN_POINT, sd->Spawn);
	attr->setAttribute(DETENTION_POINT, sd->Detention);
	attr->setAttribute(BLOCK_MOVEMENT, sd->Movement);
	attr->setAttribute(BLOCK_VISIBILITY, sd->Visibility);
	attr->setAttribute(ALIVE, 1);
}

game_sprite::game_sprite(float _x_, float _y_, float _width_, float _height_, const char * _filename_, map<int, int> _attrib_ )
{
	generalInit( _x_, _y_, _width_, _height_, _filename_ );
	
	map<int, int>::iterator itr = _attrib_.begin();
	
	// populate the attributes
	while( itr != _attrib_.end() )
	{
		attr->setAttribute( itr->first, itr->second );
		++itr;
	}	
}

game_sprite::game_sprite(float _x_, float _y_, float _width_, float _height_, const char * _filename, int vis, int mov)
{
	generalInit(_x_, _y_, _width_, _height_, _filename);
	attr->setAttribute(BLOCK_MOVEMENT, mov);
	attr->setAttribute(BLOCK_VISIBILITY, vis);
	attr->setAttribute(ALIVE, 1);
}

void game_sprite::generalInit(float _x_, float _y_, float _width_, float _height_, const char * _filename )
{
	xy(_x_, _y_);
	wh(_width_, _height_);
	texture_file = _filename;
	attr = new spriteAttribute();
	

	active = true;
	
	includeAnimation(ANIM_NONE, LoadTexture(texture_file), 0);
	useAnimation(ANIM_NONE);
	_angle = 0.0f;
	disp_x = 0.0;
	disp_y = 0.0;
}

void game_sprite::includeAnimation(int anim,const char * t, int fr){
	animations[anim] = make_pair(LoadTexture(t), fr);
}

void game_sprite::includeAnimation(int anim, GLuint t, int fr){
	animations[anim] = make_pair(t, fr);
}


void game_sprite::useAnimation(int anim){
	if (texture == anim){
		return;
	}
	if (animations.find(anim) != animations.end() ){
		texture = anim; //animations[anim].first;
	}else{
		texture = ANIM_NONE;
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
			attr->setAttribute(ALIVE, 0);
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
			if (frame >= animations[texture].second ) {
				useAnimation(ANIM_NONE);
				active = false;
			}
			break;
		case ANIM_AMBIENT:
			break;
		default:
			break;
	}
	if (frame >= animations[texture].second ) frame = 0;

	if (onscreen(disp_x, disp_y, height, width)){
		std::vector<game_sprite *>::iterator itr = sprite_list.begin();
		while( itr != sprite_list.end() )
		{
			if ( (*itr)->active == true ){
				(*itr)->animate( );
				++itr;
			}
			else{
				sprite_list.erase(itr);
			}
		}
	}
}

int game_sprite::click(int state, int x, int y)
{
	//we don't really care.
	return 0;
}

void game_sprite::xy(point pt){
	xy(pt.x, pt.y);
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
	animations.clear();
	sprite_list.clear();
	delete attr;
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

	if (active == false) return;
	
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBindTexture( GL_TEXTURE_2D, animations[texture].first );

	glMatrixMode(GL_MODELVIEW);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPushMatrix();
	
	float translated_x = 0.0f;
	float translated_x2 = 1.0f;
	float translated_y = 0.0f;
	float translated_y2 = 1.0f;

	if (texture != ANIM_NONE ) { 
		translated_x = ((float)frame * (float)width)/(animations[texture].second * (float)width);
		translated_x2 = (((float)frame + 1) * (float)width)/(animations[texture].second * (float)width);
	} 
	
	glBegin(GL_QUADS);
	glColor4f(1.0f,1.0f,1.0f,1.0f);			// Full Brightness, 0.5f == 50% Alpha ( NEW )
	
	disp_x = _x + offset_x + 0.0f;
	disp_y = _y + offset_y + 0.0f;
	
	// let's rotate some shit
	// we rotate around a origin point
	// this will generally be the center of the sprite
	float origin_x = disp_x + ( width / 2 );
	float origin_y = disp_y + ( height / 2 );
	float tex_orig_x = ( translated_x2 - translated_x ) / 2;
	float tex_orig_y = 0.5f;
	
	point corner1 = rotate( disp_x, disp_y, origin_x, origin_y, _angle );
	point corner2 = rotate( disp_x + width, disp_y, origin_x, origin_y, _angle );
	point corner3 = rotate( disp_x + width, disp_y + height, origin_x, origin_y, _angle );
	point corner4 = rotate( disp_x, disp_y + height, origin_x, origin_y, _angle );

	
	glTexCoord2d( translated_x, translated_y );		glVertex2f( corner1.x,  corner1.y );
    glTexCoord2d( translated_x2, translated_y );	glVertex2f( corner2.x,  corner2.y );
    glTexCoord2d( translated_x2, translated_y2 );	glVertex2f( corner3.x,  corner3.y );
    glTexCoord2d( translated_x, translated_y2 );	glVertex2f( corner4.x,  corner4.y );
	
	glEnd();
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	
	// run through the drawables
	// Thomas. This is neat.
	// neato burrito.
	
	//lets make rules for drawables:
	//1 - Do not draw if you're not onscreen.
	if (onscreen(disp_x, disp_y, height, width)){
		for ( int i = 0; i < drawables.size(); i++ ){
			drawables[i]->draw( disp_x, disp_y, _angle );
		}

		std::vector<game_sprite *>::iterator itr = sprite_list.begin();
		while( itr != sprite_list.end() )
		{
			if ( (*itr)->active == true ){
				(*itr)->draw( offset_x, offset_y );
				++itr;
			}
			else{
				sprite_list.erase(itr);
			}
		}
	}
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

void game_sprite::movement(){
	if (!onscreen(disp_x, disp_y, height, width)) return;
	
	float delta = 0.8;
	if ((move_right > 0) || (move_left > 0) || (move_up > 0) || (move_down > 0)){
		if (texture != animations[ANIM_WALK].first) {
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

	if (onscreen(disp_x, disp_y, height, width)){
		std::vector<game_sprite *>::iterator itr = sprite_list.begin();
		while( itr != sprite_list.end() )
		{
			if ( (*itr)->active == true ){
				(*itr)->movement( );
				++itr;
			}
			else{
				sprite_list.erase(itr);
			}
		}
	}
}

void game_sprite::captured()
{
	//um... most sprites might not care, I guess.
}

void game_sprite::setDrawable( drawable * pDrawable )
{
	drawables.push_back( pDrawable );
}

void game_sprite::includeSprite( game_sprite * pSprite )
{
	sprite_list.push_back( pSprite );
}

float game_sprite::distance(point target)
{
      return sqrt( pow(target.x - _x, 2) + pow(target.y - _y, 2) );
}

point game_sprite::center()
{
	return point(_x + ( width / 2), _y + ( height / 2));
}


/**************
 We may need to use this for texture/sprite cleanup in an emergency
 **************/

void texture_cleanup(){
	int i;
	for (i = 0; i < master_texture_list.size(); i++){
		glDeleteTextures( 1, &master_texture_list[i].second );
	}
	master_texture_list.clear();
}




