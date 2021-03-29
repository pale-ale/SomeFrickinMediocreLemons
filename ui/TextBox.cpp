#include "TextBox.h"
//wip will modify on Saturday please do not touch until then
TextBox::TextBox(UISystem* ui):UIElement(ui){

}
TextBox::TextBox(UISystem* ui, string content):UIElement(ui){
    this->content=content;
    UpdateContent();
}
TextBox::TextBox(UISystem* ui, unsigned int width, unsigned int height):UIElement(ui){
this->width = width;
this->height = height;
UpdateContent();
}
TextBox::TextBox(UISystem* ui, unsigned int width, unsigned int height, string content):UIElement(ui){
this->width = width;
this->height = height;
this->content = content;
UpdateContent();
}

bool TextBox::UpdateContent(){
    unsigned int character = 0;
    list<string> wordlist;
    auto iterator = wordlist.begin();
       //fill the wordlist with content
    while(character < this->content.length()){

    }
    sf::Text uicontentboundaries = sf::Text();
    //clear current Text in ui
    uicontent.setString("");
    //foreach element in wordlist check if width is to large
    while(iterator != wordlist.end()){
        uicontentboundaries.setString(this->uicontent.getString());
        uicontentboundaries.setString(uicontentboundaries.getString()+*iterator);
        if(uicontentboundaries.getGlobalBounds().width > this->width){
            this->uicontent.setString(this->uicontent.getString() + "\n" + *iterator);
        }
        else{
            uicontentboundaries.setString(this->uicontent.getString() + *iterator);
        }
        if(this->uicontent.getGlobalBounds().height > this->height || this->uicontent.getGlobalBounds().width > this->width){
            return false;
        }
    }
    return true;
}

void TextBox::initializeSubComponents(){
    UIElement::initializeSubComponents();
    ui->addListener(static_pointer_cast<UIElement>(weak_from_this().lock()));
}

bool TextBox::ChangeContent(char* content){
    this->content=content;
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}

bool TextBox::ChangeSize(unsigned int size){
    this->uicontent.setCharacterSize(size);
    if(this->UpdateContent()){
        return true;
    }
    else{
        return false;
    }
}
