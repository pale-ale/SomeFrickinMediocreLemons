#include "QuickTextBox.h"

QuickTextBox::QuickTextBox(UISystem *ui, string text, bool autoWrap) : UIElement(ui),
    autoWrap{autoWrap}, originalText{text}
{
    font.loadFromFile(Settings::validFontPath);
    textDisplay.setFont(font);
    textDisplay.setPosition({100, 100});
    textDisplay.setCharacterSize(fontSize);
    updateContent();
}

void QuickTextBox::updateContent()
{
    string tmp = originalText; //copy
    auto start = tmp.begin();
    auto end = tmp.end();
    while (start != end)
    {
        if (*start == '\n')
        {
            tmp.erase(start);
        }
        ++start;
    }
    size_t lastWordBegin;
    size_t lastWordEnd;
    bool currentlyInsideWord = false;
    if (autoWrap)
    {
        for (size_t i = 1; i < tmp.length() + 1; i++)
        {
            char character = tmp[i];
            if (!currentlyInsideWord && character != ' ')
            {
                lastWordBegin = i;
                currentlyInsideWord = true;
            }
            if (currentlyInsideWord && character == ' ')
            {
                lastWordEnd = i;
                currentlyInsideWord = false;
            }
            if ((i + 1) % maxCharacterCountPerLine == 0)
            {
                //when reaching the end of the line, we want to wrap
                if (currentlyInsideWord)
                {
                    // we would now be splitting a word
                    tmp.insert(lastWordBegin, "\n");
                }
                else
                {
                    //get rid of pesky spaces after a newline
                    if (tmp[i] == ' ')
                    {
                        tmp.erase(i, 1);
                    }
                    tmp.insert(i++, "\n");
                }
            }
        }
    }
    formattedText = std::move(tmp);
    textDisplay.setString(formattedText);
}

void QuickTextBox::setText(const string &newText)
{
    originalText = newText;
    updateContent();
}

void QuickTextBox::setCharacterSize(unsigned int newFontSize)
{
    fontSize = newFontSize;
    textDisplay.setCharacterSize(fontSize);
}
