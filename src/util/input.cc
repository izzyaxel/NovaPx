#include "input.hh"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

//----Externs----//
std::unordered_map<Input::Action, bool> Input::immediateModeKeystates;
std::unordered_map<Input::Action, double> Input::pressLength;
//----Externs----//

uint8_t const *keystate;
std::unordered_map<Input::Key, Input::Action> keymap;
SDL_GameController *controller = nullptr;

namespace Input
{
	std::vector<TriggerModePair> triggerModeKeybinds;
	
	void init()
	{
		SDL_Init(SDL_INIT_GAMECONTROLLER);
		
		for(int i = 0; i < SDL_NumJoysticks(); i++)
		{
			if(SDL_IsGameController(i))
			{
				controller = SDL_GameControllerOpen(i);
				break;
			}
		}
		keystate = SDL_GetKeyboardState(nullptr);
	}
	
	void updateImmediateModeKbd()
	{
		//TODO handle making deltaTT with global or player specific timescale
		if(SDL_IsTextInputActive() == SDL_TRUE)
		{
			immediateModeKeystates[keymap[Key::KEY_ESC]] = keystate[SDL_SCANCODE_ESCAPE] != 0;
			immediateModeKeystates[keymap[Key::KEY_F1]] = keystate[SDL_SCANCODE_F1] != 0;
			immediateModeKeystates[keymap[Key::KEY_F2]] = keystate[SDL_SCANCODE_F2] != 0;
			immediateModeKeystates[keymap[Key::KEY_F3]] = keystate[SDL_SCANCODE_F3] != 0;
			immediateModeKeystates[keymap[Key::KEY_F4]] = keystate[SDL_SCANCODE_F4] != 0;
			immediateModeKeystates[keymap[Key::KEY_F5]] = keystate[SDL_SCANCODE_F5] != 0;
			immediateModeKeystates[keymap[Key::KEY_F6]] = keystate[SDL_SCANCODE_F6] != 0;
			immediateModeKeystates[keymap[Key::KEY_F7]] = keystate[SDL_SCANCODE_F7] != 0;
			immediateModeKeystates[keymap[Key::KEY_F8]] = keystate[SDL_SCANCODE_F8] != 0;
			immediateModeKeystates[keymap[Key::KEY_F9]] = keystate[SDL_SCANCODE_F9] != 0;
			immediateModeKeystates[keymap[Key::KEY_F10]] = keystate[SDL_SCANCODE_F10] != 0;
			immediateModeKeystates[keymap[Key::KEY_F11]] = keystate[SDL_SCANCODE_F11] != 0;
			immediateModeKeystates[keymap[Key::KEY_F12]] = keystate[SDL_SCANCODE_F12] != 0;
			
			immediateModeKeystates[keymap[Key::KEY_PRNTSCRN]] = keystate[SDL_SCANCODE_PRINTSCREEN] != 0;
			immediateModeKeystates[keymap[Key::KEY_NUMLCK]] = keystate[SDL_SCANCODE_NUMLOCKCLEAR] != 0;
			immediateModeKeystates[keymap[Key::KEY_PAUSE]] = keystate[SDL_SCANCODE_PAUSE] != 0;
			immediateModeKeystates[keymap[Key::KEY_INSERT]] = keystate[SDL_SCANCODE_INSERT] != 0;
			immediateModeKeystates[keymap[Key::KEY_HOME]] = keystate[SDL_SCANCODE_HOME] != 0;
			immediateModeKeystates[keymap[Key::KEY_PGUP]] = keystate[SDL_SCANCODE_PAGEUP] != 0;
			immediateModeKeystates[keymap[Key::KEY_DEL]] = keystate[SDL_SCANCODE_DELETE] != 0;
			immediateModeKeystates[keymap[Key::KEY_END]] = keystate[SDL_SCANCODE_END] != 0;
			immediateModeKeystates[keymap[Key::KEY_PGDOWN]] = keystate[SDL_SCANCODE_PAGEDOWN] != 0;
			immediateModeKeystates[keymap[Key::KEY_LARROW]] = keystate[SDL_SCANCODE_LEFT] != 0;
			immediateModeKeystates[keymap[Key::KEY_RARROW]] = keystate[SDL_SCANCODE_RIGHT] != 0;
			immediateModeKeystates[keymap[Key::KEY_UARROW]] = keystate[SDL_SCANCODE_UP] != 0;
			immediateModeKeystates[keymap[Key::KEY_DARROW]] = keystate[SDL_SCANCODE_DOWN] != 0;
			
			immediateModeKeystates[keymap[Key::KEY_GRAVE]] = keystate[SDL_SCANCODE_GRAVE] != 0;
			immediateModeKeystates[keymap[Key::KEY_1]] = keystate[SDL_SCANCODE_1] != 0;
			immediateModeKeystates[keymap[Key::KEY_2]] = keystate[SDL_SCANCODE_2] != 0;
			immediateModeKeystates[keymap[Key::KEY_3]] = keystate[SDL_SCANCODE_3] != 0;
			immediateModeKeystates[keymap[Key::KEY_4]] = keystate[SDL_SCANCODE_4] != 0;
			immediateModeKeystates[keymap[Key::KEY_5]] = keystate[SDL_SCANCODE_5] != 0;
			immediateModeKeystates[keymap[Key::KEY_6]] = keystate[SDL_SCANCODE_6] != 0;
			immediateModeKeystates[keymap[Key::KEY_7]] = keystate[SDL_SCANCODE_7] != 0;
			immediateModeKeystates[keymap[Key::KEY_8]] = keystate[SDL_SCANCODE_8] != 0;
			immediateModeKeystates[keymap[Key::KEY_9]] = keystate[SDL_SCANCODE_9] != 0;
			immediateModeKeystates[keymap[Key::KEY_0]] = keystate[SDL_SCANCODE_0] != 0;
			immediateModeKeystates[keymap[Key::KEY_MINUS]] = keystate[SDL_SCANCODE_MINUS] != 0;
			immediateModeKeystates[keymap[Key::KEY_EQUALS]] = keystate[SDL_SCANCODE_EQUALS] != 0;
			immediateModeKeystates[keymap[Key::KEY_BACKSPACE]] = keystate[SDL_SCANCODE_BACKSPACE] != 0;
			
			immediateModeKeystates[keymap[Key::KEY_Q]] = keystate[SDL_SCANCODE_Q] != 0;
			immediateModeKeystates[keymap[Key::KEY_W]] = keystate[SDL_SCANCODE_W] != 0;
			immediateModeKeystates[keymap[Key::KEY_E]] = keystate[SDL_SCANCODE_E] != 0;
			immediateModeKeystates[keymap[Key::KEY_R]] = keystate[SDL_SCANCODE_R] != 0;
			immediateModeKeystates[keymap[Key::KEY_T]] = keystate[SDL_SCANCODE_T] != 0;
			immediateModeKeystates[keymap[Key::KEY_Y]] = keystate[SDL_SCANCODE_Y] != 0;
			immediateModeKeystates[keymap[Key::KEY_U]] = keystate[SDL_SCANCODE_U] != 0;
			immediateModeKeystates[keymap[Key::KEY_I]] = keystate[SDL_SCANCODE_I] != 0;
			immediateModeKeystates[keymap[Key::KEY_O]] = keystate[SDL_SCANCODE_O] != 0;
			immediateModeKeystates[keymap[Key::KEY_P]] = keystate[SDL_SCANCODE_P] != 0;
			immediateModeKeystates[keymap[Key::KEY_RBRACKET]] = keystate[SDL_SCANCODE_RIGHTBRACKET] != 0;
			immediateModeKeystates[keymap[Key::KEY_LBRACKET]] = keystate[SDL_SCANCODE_LEFTBRACKET] != 0;
			immediateModeKeystates[keymap[Key::KEY_BSLASH]] = keystate[SDL_SCANCODE_BACKSLASH] != 0;
			
			immediateModeKeystates[keymap[Key::KEY_CAPSLCK]] = keystate[SDL_SCANCODE_CAPSLOCK] != 0;
			immediateModeKeystates[keymap[Key::KEY_A]] = keystate[SDL_SCANCODE_A] != 0;
			immediateModeKeystates[keymap[Key::KEY_S]] = keystate[SDL_SCANCODE_S] != 0;
			immediateModeKeystates[keymap[Key::KEY_D]] = keystate[SDL_SCANCODE_D] != 0;
			immediateModeKeystates[keymap[Key::KEY_F]] = keystate[SDL_SCANCODE_F] != 0;
			immediateModeKeystates[keymap[Key::KEY_G]] = keystate[SDL_SCANCODE_G] != 0;
			immediateModeKeystates[keymap[Key::KEY_H]] = keystate[SDL_SCANCODE_H] != 0;
			immediateModeKeystates[keymap[Key::KEY_J]] = keystate[SDL_SCANCODE_J] != 0;
			immediateModeKeystates[keymap[Key::KEY_K]] = keystate[SDL_SCANCODE_K] != 0;
			immediateModeKeystates[keymap[Key::KEY_L]] = keystate[SDL_SCANCODE_L] != 0;
			immediateModeKeystates[keymap[Key::KEY_SEMICOLON]] = keystate[SDL_SCANCODE_SEMICOLON] != 0;
			immediateModeKeystates[keymap[Key::KEY_APOSTRAPHE]] = keystate[SDL_SCANCODE_APOSTROPHE] != 0;
			immediateModeKeystates[keymap[Key::KEY_RETURN]] = keystate[SDL_SCANCODE_RETURN] != 0;
			
			immediateModeKeystates[keymap[Key::KEY_LSHIFT]] = keystate[SDL_SCANCODE_LSHIFT] != 0;
			immediateModeKeystates[keymap[Key::KEY_Z]] = keystate[SDL_SCANCODE_Z] != 0;
			immediateModeKeystates[keymap[Key::KEY_X]] = keystate[SDL_SCANCODE_X] != 0;
			immediateModeKeystates[keymap[Key::KEY_C]] = keystate[SDL_SCANCODE_C] != 0;
			immediateModeKeystates[keymap[Key::KEY_V]] = keystate[SDL_SCANCODE_V] != 0;
			immediateModeKeystates[keymap[Key::KEY_B]] = keystate[SDL_SCANCODE_B] != 0;
			immediateModeKeystates[keymap[Key::KEY_N]] = keystate[SDL_SCANCODE_N] != 0;
			immediateModeKeystates[keymap[Key::KEY_M]] = keystate[SDL_SCANCODE_M] != 0;
			immediateModeKeystates[keymap[Key::KEY_COMMA]] = keystate[SDL_SCANCODE_COMMA] != 0;
			immediateModeKeystates[keymap[Key::KEY_PERIOD]] = keystate[SDL_SCANCODE_PERIOD] != 0;
			immediateModeKeystates[keymap[Key::KEY_FSLASH]] = keystate[SDL_SCANCODE_SLASH] != 0;
			immediateModeKeystates[keymap[Key::KEY_RSHIFT]] = keystate[SDL_SCANCODE_RSHIFT] != 0;
			
			immediateModeKeystates[keymap[Key::KEY_LCTRL]] = keystate[SDL_SCANCODE_LCTRL] != 0;
			immediateModeKeystates[keymap[Key::KEY_LALT]] = keystate[SDL_SCANCODE_LALT] != 0;
			immediateModeKeystates[keymap[Key::KEY_SPACE]] = keystate[SDL_SCANCODE_SPACE] != 0;
			immediateModeKeystates[keymap[Key::KEY_RALT]] = keystate[SDL_SCANCODE_RALT] != 0;
			immediateModeKeystates[keymap[Key::KEY_APP]] = keystate[SDL_SCANCODE_APPLICATION] != 0;
			immediateModeKeystates[keymap[Key::KEY_MENU]] = keystate[SDL_SCANCODE_MENU] != 0;
			immediateModeKeystates[keymap[Key::KEY_RCTRL]] = keystate[SDL_SCANCODE_RCTRL] != 0;
			
			//TODO scroll lock, break etc
		}
	}
	
	void bindImmediateModeKey(Key key, Action action)
	{
		keymap[key] = action;
	}
	
	void bindTriggerModeKey(Key key, std::function<void (bool)> callback)
	{
		triggerModeKeybinds.push_back(TriggerModePair{key, callback});
	}
	
	Action getBoundAction(Key key)
	{
		return keymap[key];
	}
	
	Key getBoundKey(Action action)
	{
		for(auto const &kb : keymap) if(kb.second == action) return kb.first;
		return Key::KEY_UNKNOWN;
	}
}
