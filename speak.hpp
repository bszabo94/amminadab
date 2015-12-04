#ifndef SPEAK_HPP
#define SPEAK_HPP

/**
 * @brief Implements basic verbal communation and audio-storage for the project.
 *
 * @file speak.hpp
 * @author  Szabó Bence
 * @version 0.0.1
 *
 * @section LICENSE
 *
 * Copyright (C) 2015 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * JACOB, https://github.com/nbatfai/jacob
 *
 * "The son of Isaac is Jacob." The project called Jacob is an experiment
 * to replace Isaac's (GUI based) visual imagination with a character console.
 *
 * ISAAC, https://github.com/nbatfai/isaac
 *
 * "The son of Samu is Isaac." The project called Isaac is a case study
 * of using deep Q learning with neural networks for predicting the next
 * sentence of a conversation.
 *
 * SAMU, https://github.com/nbatfai/samu
 *
 * The main purpose of this project is to allow the evaluation and
 * verification of the results of the paper entitled "A disembodied
 * developmental robotic agent called Samu Bátfai". It is our hope
 * that Samu will be the ancestor of developmental robotics chatter
 * bots that will be able to chat in natural language like humans do.
 *
 */

#include <cstring>
#include <sstream>
#include <malloc.h>
#include <fstream>
#include <string.h>
#include <cstdio>
#include <stdio.h>

#include <speak_lib.h> //the program uses the speak library (package: libespeak-dev)

/*
 * SpeakController objects are used to audio output from text input, using espeak library.
 */
class SpeakController {
  
  private:
    
    espeak_POSITION_TYPE position_type;
    espeak_AUDIO_OUTPUT output;
    
    char *path;
    int Buflength, Options, Run;
    void* user_data;
    
    std::string text, voice;
    
    unsigned int size, flags;
    /*
     * Starting character of the text in the output.
     */
    unsigned int position;
    /*
     * Ending character of the text in the output.
     */
    unsigned int end_position;
    
    unsigned int* unique_identifier;
    
    bool synced;
  
  public:
    
    SpeakController() {
      
      //////////////////////////
      //Initializing Variables//
      //////////////////////////
      
      path = NULL;
      Options = 0;
      Buflength = 500;
      output = AUDIO_OUTPUT_PLAYBACK;
      voice = "default";
      Run = 1;
      text = "";
      size = text.length()+1;
      position = 0;
      end_position = 0;
      flags = espeakCHARS_AUTO;
      synced = true;
      unique_identifier = NULL;
      
      
      espeak_Initialize(output, Buflength, path, Options ); // Must be called before any synthesis functions are called.
    }
    
    std::string getText() {
      return this->text;
    }
        
    
    /*
     * Converts the input text from string to char* in order of wider variety of use.
    */
    void setText(std::string &newText) {
      
      text = newText;
     this->setSize(this->text.length()+1);
      
    }
      
    void setVoice(std::string newVoice) {
      voice = newVoice;
    }
    
    void setSize(unsigned int newSize) {
      size = newSize;
    }

    /*
     * Plays the text stored in the 'text' variable.
     * If synced is true, the program waits the audio to end before moving to the next task.
     */
    void playAudio() {
      if (synced) {
	
	//voice is set
	espeak_SetVoiceByName(voice.c_str());
	
	//data is being converted to audio
	espeak_Synth( text.c_str(), size, position, position_type, end_position, flags, unique_identifier, user_data );
	
	//returns when the audio finished playing
	espeak_Synchronize();
	
      }
      else {
	
	//voice is set
	espeak_SetVoiceByName(voice.c_str());
	
	//data is being converted to audio
	espeak_Synth( text.c_str(), size, position, position_type, end_position, flags, unique_identifier, user_data );
	
      }
      
    }
    
    
    /////////////////////////////////////////////
    //Get and Set methods for private variables//
    /////////////////////////////////////////////
    
    bool getSynced() {
      return this->synced;
    }
    
    void setSynced(bool newSynced) {
      this->synced = newSynced;
    }
    
    unsigned int getSize() {
      return this->size;
    }
    
    unsigned int getPosition() {
      return this->position;
    }
    
    espeak_POSITION_TYPE getPosType() {
      return this->position_type;
    }
    
    unsigned int getFlags() {
      return this->flags;
    }
    
    unsigned int getEndPos() {
      return this->end_position;
    }
    
    void* getUD() {
      return this->user_data;
    }
    
    unsigned int* getUI() {
      return this->unique_identifier;
    }
};


#endif