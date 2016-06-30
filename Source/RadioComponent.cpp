/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "RadioComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
RadioComponent::RadioComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]
	lafradio = new LAFRadio();
	addAndMakeVisible(title = new Label("LAF"));
	title->setColour(Label::textColourId, Colours::red);
	title->setText("Radio Custom",NotificationType::dontSendNotification);
	for (size_t i = 0; i < 3; i++)
	{
	ToggleButton* toggle = new ToggleButton("Radio of "+String(i));
	
	toggle->setRadioGroupId(1);
	toggle->addListener(this);	
	
	toggle->setLookAndFeel(lafradio);
	toggleButton.add(toggle);
	}
	
	for (auto item : toggleButton) {
		addAndMakeVisible(item);
	}
	
    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

RadioComponent::~RadioComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

	toggleButton.clear();


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void RadioComponent::paint(Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void RadioComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
	Rectangle<int> area = this->getBounds().reduced(5);
	
	title->setBounds(area.removeFromTop(20));
	for (auto item:toggleButton) {
		area.removeFromTop(20);
		item->setBounds(area.removeFromTop(20));
		
	}
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void RadioComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

   

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="RadioComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TOGGLEBUTTON name="Radio Off" id="a54883cf5f2332a8" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="16 48 150 24" buttonText="Radio Off"
                connectedEdges="0" needsCallback="1" radioGroupId="1" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
