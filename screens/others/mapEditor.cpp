#include "mapEditor.h"

struct fieldData
{
    int player;
    vector<string> parts;

    void addPart(string part)
    {

    }

    void clearPart()
    {

    }
};
vector<fieldData> fields;

mapEditor::mapEditor()
{
    draw();
}

void mapEditor::draw()
{
    addTitle("Editor");
}
