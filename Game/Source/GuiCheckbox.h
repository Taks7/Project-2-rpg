#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiCheckbox : public GuiControl
{
public:

	GuiCheckbox(uint32 id, SDL_Rect bounds, const char* text);
	virtual ~GuiCheckbox();

	bool Update(float dt);
	bool PostUpdate();
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;
};

#endif // __GUIBUTTON_H__