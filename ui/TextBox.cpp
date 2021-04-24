#include "TextBox.h"
//wip will modify on Saturday please do not touch until then
TextBox::TextBox(UISystem* ui, sf::Vector2f size, string content="", bool autoresize = true):UIElement(ui){
    this->autoresize = autoresize;
    this->size = size;
    this->content = content;
    UpdateContent();
}

bool TextBox::UpdateContent(){
    list<string> wordlist;
    auto iterator = wordlist.begin();
    //fill the wordlist with content
    istringstream iss(content);
    string token;
    while(getline(iss, token, ' ')){
        wordlist.push_back(token);
    }
    sf::Text uicontentboundaries = sf::Text();
    //clear current Text in ui
    uicontent.setString("");
    //foreach element in wordlist check if width is to large
    //if the autoresize is off show hovering text instead
    while(iterator != wordlist.end()){
        uicontentboundaries.setString(this->uicontent.getString());
        uicontentboundaries.setString(uicontentboundaries.getString()+*iterator);
        if(uicontentboundaries.getGlobalBounds().width > this->size.x){
            this->uicontent.setString(this->uicontent.getString() + "\n" + *iterator);
        }
        else{
            uicontentboundaries.setString(this->uicontent.getString() + *iterator);
        }
        iterator++;
        //if the uicontent does not fit to y size the need to resize the character size and restart the procedure
        if(this->uicontent.getGlobalBounds().height > this->size.y || this->uicontent.getGlobalBounds().width > this->size.x){
            if(this->uicontent.getCharacterSize()!=0){
            this->uicontent.setCharacterSize(this->uicontent.getCharacterSize()-1);
            //begin the procedure again, because character size has changed
            iterator = wordlist.begin();
            uicontent.setString("");
            }
            else{
                return false;
            }
        }
    }
    return true;
}

//this is for hovering text later if it does not fit to textbox
void TextBox::initializeSubComponents(){
    UIElement::initializeSubComponents();
    ui->addEventListener(static_pointer_cast<UIElement>(weak_from_this().lock()));
}

bool TextBox::ChangeContent(string content){
    this->content=content;
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}

bool TextBox::ChangeCharacterSize(unsigned int size){
    this->uicontent.setCharacterSize(size);
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}
