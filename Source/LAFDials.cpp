/*
  ==============================================================================

    LAFDials.cpp
    Created: 1 Jun 2016 11:38:08am
    Author:  khoi.dang

  ==============================================================================
*/


#include "LAFDials.h"
LAFDialsStyle::LAFDialsStyle()
{
}

LAFDialsStyle::LAFDialsStyle(Slider* slider, Colour brColor, String title, String dv)
{
	
	slider->setName(title);
	slider->setComponentID(dv);
	slider->setColour(Slider::textBoxBackgroundColourId, Colours::black);
	slider->setColour(Slider::textBoxTextColourId, Colours::white);
	slider->setSliderStyle(Slider::Rotary);
	slider->setTextBoxStyle(Slider::TextBoxBelow, false, 38, 16);
}

LAFDialsStyle::~LAFDialsStyle()
{
}

Slider::SliderLayout LAFDialsStyle::getSliderLayout(Slider & slider)
{
	// 1. compute the actually visible textBox size from the slider textBox size and some additional constraints

	int minXSpace = 0;
	int minYSpace = 0;

	Slider::TextEntryBoxPosition textBoxPos = slider.getTextBoxPosition();

	if (textBoxPos == Slider::TextBoxLeft || textBoxPos == Slider::TextBoxRight)
		minXSpace = 30;
	else
		minYSpace = 15;

	Rectangle<int> localBounds = slider.getLocalBounds();

	const int textBoxWidth = jmax(0, jmin(slider.getTextBoxWidth(), localBounds.getWidth() - minXSpace));
	const int textBoxHeight = jmax(0, jmin(slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));

	Slider::SliderLayout layout;

	// 2. set the textBox bounds

	if (textBoxPos != Slider::NoTextBox)
	{
		if (slider.isBar())
		{
			layout.textBoxBounds = localBounds;
		}
		else
		{
			layout.textBoxBounds.setWidth(textBoxWidth);
			layout.textBoxBounds.setHeight(textBoxHeight);

			if (textBoxPos == Slider::TextBoxLeft)           layout.textBoxBounds.setX(0);
			else if (textBoxPos == Slider::TextBoxRight)     layout.textBoxBounds.setX(localBounds.getWidth() - textBoxWidth);
			else /* above or below -> centre horizontally */ layout.textBoxBounds.setX((localBounds.getWidth() - textBoxWidth) / 2);

			if (textBoxPos == Slider::TextBoxAbove)          layout.textBoxBounds.setY(0);
			else if (textBoxPos == Slider::TextBoxBelow)     layout.textBoxBounds.setY((localBounds.getHeight() - textBoxHeight));
			else /* left or right -> centre vertically */    layout.textBoxBounds.setY((localBounds.getHeight() - textBoxHeight) / 2);
		}
	}

	// 3. set the slider bounds

	layout.sliderBounds = localBounds;

	if (slider.isBar())
	{
		layout.sliderBounds.reduce(1, 1);   // bar border
	}
	else
	{
		if (textBoxPos == Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft(textBoxWidth);
		else if (textBoxPos == Slider::TextBoxRight) layout.sliderBounds.removeFromRight(textBoxWidth);
		else if (textBoxPos == Slider::TextBoxAbove) layout.sliderBounds.removeFromTop(textBoxHeight);
		else if (textBoxPos == Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom(textBoxHeight);

		const int thumbIndent = getSliderThumbRadius(slider);

		if (slider.isHorizontal())    layout.sliderBounds.reduce(thumbIndent, 0);
		else if (slider.isVertical()) layout.sliderBounds.reduce(0, thumbIndent);
	}

	return layout;
}
void LAFDialsStyle::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	float rotaryStartAngle, float rotaryEndAngle, Slider& slider) 
{
	const float diameter = jmin(width, height) + 5.0f;
	const float radius = (diameter / 2.0f) * std::cos(float_Pi / 4.0f);
	const float centreX = x + width * 0.5f;
	const float centreY = y + height * 0.5f;
	const float rx = centreX - radius;
	const float ry = centreY - radius;
	const float rw = radius * 2.0f;
	const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
	const bool isEnabled =  slider.isEnabled();
	
	const Colour baseColour(slider.isEnabled() ? slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 0.8f : 1.0f)
		: Colour(0x80808080));

	Rectangle<float> m(rx, ry, rw, rw);
	Rectangle<float> r = m.reduced(2.0f);
	AffineTransform t(AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));

	float x1 = r.getTopLeft().getX(), y1 = r.getTopLeft().getY(), x2 = r.getBottomLeft().getX(), y2 = r.getBottomLeft().getY();
	t.transformPoints(x1, y1, x2, y2);
#pragma region Line

	const float step = 1.0f / 21.0f;
	const float angle1 = rotaryStartAngle + 0 * (rotaryEndAngle - rotaryStartAngle);
	const float angle2 = rotaryStartAngle + step * (rotaryEndAngle - rotaryStartAngle);
	const float angle3 = rotaryStartAngle + (step * 2) * (rotaryEndAngle - rotaryStartAngle);
	const float angle4 = rotaryStartAngle + (step * 3) * (rotaryEndAngle - rotaryStartAngle);
	const float angle5 = rotaryStartAngle + (step * 4) * (rotaryEndAngle - rotaryStartAngle);
	const float angle6 = rotaryStartAngle + (step * 5) * (rotaryEndAngle - rotaryStartAngle);
	const float angle7 = rotaryStartAngle + (step * 6) * (rotaryEndAngle - rotaryStartAngle);
	const float angle8 = rotaryStartAngle + (step * 7) * (rotaryEndAngle - rotaryStartAngle);
	const float angle9 = rotaryStartAngle + (step * 8) * (rotaryEndAngle - rotaryStartAngle);
	const float angle10 = rotaryStartAngle + (step * 9) * (rotaryEndAngle - rotaryStartAngle);
	const float angle11 = rotaryStartAngle + (step * 10) * (rotaryEndAngle - rotaryStartAngle);
	const float angle12 = rotaryStartAngle + (step * 11) * (rotaryEndAngle - rotaryStartAngle);
	const float angle13 = rotaryStartAngle + (step * 12) * (rotaryEndAngle - rotaryStartAngle);
	const float angle14 = rotaryStartAngle + (step * 13) * (rotaryEndAngle - rotaryStartAngle);
	const float angle15 = rotaryStartAngle + (step * 14) * (rotaryEndAngle - rotaryStartAngle);
	const float angle16 = rotaryStartAngle + (step * 15) * (rotaryEndAngle - rotaryStartAngle);
	const float angle17 = rotaryStartAngle + (step * 16) * (rotaryEndAngle - rotaryStartAngle);
	const float angle18 = rotaryStartAngle + (step * 17) * (rotaryEndAngle - rotaryStartAngle);
	const float angle19 = rotaryStartAngle + (step * 18) * (rotaryEndAngle - rotaryStartAngle);
	const float angle20 = rotaryStartAngle + (step * 19) * (rotaryEndAngle - rotaryStartAngle);
	const float angle21 = rotaryStartAngle + (step * 20) * (rotaryEndAngle - rotaryStartAngle);
	const float angle22 = rotaryStartAngle + (step * 21) * (rotaryEndAngle - rotaryStartAngle);

	Line<float> l1(centreX, ry, centreX, centreY);
	Line<float> l2(centreX, ry, centreX, centreY);
	Line<float> l3(centreX, ry, centreX, centreY);
	Line<float> l4(centreX, ry, centreX, centreY);
	Line<float> l5(centreX, ry, centreX, centreY);
	Line<float> l6(centreX, ry, centreX, centreY);
	Line<float> l7(centreX, ry, centreX, centreY);
	Line<float> l8(centreX, ry, centreX, centreY);
	Line<float> l9(centreX, ry, centreX, centreY);
	Line<float> l10(centreX, ry, centreX, centreY);
	Line<float> l11(centreX, ry, centreX, centreY);
	Line<float> l12(centreX, ry, centreX, centreY);
	Line<float> l13(centreX, ry, centreX, centreY);
	Line<float> l14(centreX, ry, centreX, centreY);
	Line<float> l15(centreX, ry, centreX, centreY);
	Line<float> l16(centreX, ry, centreX, centreY);
	Line<float> l17(centreX, ry, centreX, centreY);
	Line<float> l18(centreX, ry, centreX, centreY);
	Line<float> l19(centreX, ry, centreX, centreY);
	Line<float> l20(centreX, ry, centreX, centreY);
	Line<float> l21(centreX, ry, centreX, centreY);
	Line<float> l22(centreX, ry, centreX, centreY);

	l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
	l2.applyTransform(AffineTransform::rotation(angle2, centreX, centreY));
	l3.applyTransform(AffineTransform::rotation(angle3, centreX, centreY));
	l4.applyTransform(AffineTransform::rotation(angle4, centreX, centreY));
	l5.applyTransform(AffineTransform::rotation(angle5, centreX, centreY));
	l6.applyTransform(AffineTransform::rotation(angle6, centreX, centreY));
	l7.applyTransform(AffineTransform::rotation(angle7, centreX, centreY));
	l8.applyTransform(AffineTransform::rotation(angle8, centreX, centreY));
	l9.applyTransform(AffineTransform::rotation(angle9, centreX, centreY));
	l10.applyTransform(AffineTransform::rotation(angle10, centreX, centreY));
	l11.applyTransform(AffineTransform::rotation(angle11, centreX, centreY));
	l12.applyTransform(AffineTransform::rotation(angle12, centreX, centreY));
	l13.applyTransform(AffineTransform::rotation(angle13, centreX, centreY));
	l14.applyTransform(AffineTransform::rotation(angle14, centreX, centreY));
	l15.applyTransform(AffineTransform::rotation(angle15, centreX, centreY));
	l16.applyTransform(AffineTransform::rotation(angle16, centreX, centreY));
	l17.applyTransform(AffineTransform::rotation(angle17, centreX, centreY));
	l18.applyTransform(AffineTransform::rotation(angle18, centreX, centreY));
	l19.applyTransform(AffineTransform::rotation(angle19, centreX, centreY));
	l20.applyTransform(AffineTransform::rotation(angle20, centreX, centreY));
	l21.applyTransform(AffineTransform::rotation(angle21, centreX, centreY));
	l22.applyTransform(AffineTransform::rotation(angle22, centreX, centreY));
	g.setColour(angle > angle1 ? Colours::orange : Colours::black);
	g.drawLine(l1, 2);
	g.setColour(angle > angle2 ? Colours::orange : Colours::black);
	g.drawLine(l2, 2);
	g.setColour(angle > angle3 ? Colours::orange : Colours::black);
	g.drawLine(l3, 2);
	g.setColour(angle > angle4 ? Colours::orange : Colours::black);
	g.drawLine(l4, 2);
	g.setColour(angle > angle5 ? Colours::orange : Colours::black);
	g.drawLine(l5, 2);
	g.setColour(angle > angle6 ? Colours::orange : Colours::black);
	g.drawLine(l6, 2);
	g.setColour(angle > angle7 ? Colours::orange : Colours::black);
	g.drawLine(l7, 2);
	g.setColour(angle > angle8 ? Colours::orange : Colours::black);
	g.drawLine(l8, 2);
	g.setColour(angle > angle9 ? Colours::orange : Colours::black);
	g.drawLine(l9, 2);
	g.setColour(angle > angle10 ? Colours::orange : Colours::black);
	g.drawLine(l10, 2);
	g.setColour(angle > angle11 ? Colours::orange : Colours::black);
	g.drawLine(l11, 2);
	g.setColour(angle > angle12 ? Colours::orange : Colours::black);
	g.drawLine(l12, 2);
	g.setColour(angle > angle13 ? Colours::orange : Colours::black);
	g.drawLine(l13, 2);
	g.setColour(angle > angle14 ? Colours::orange : Colours::black);
	g.drawLine(l14, 2);
	g.setColour(angle > angle15 ? Colours::orange : Colours::black);
	g.drawLine(l15, 2);
	g.setColour(angle > angle16 ? Colours::orange : Colours::black);
	g.drawLine(l16, 2);
	g.setColour(angle > angle17 ? Colours::orange : Colours::black);
	g.drawLine(l17, 2);
	g.setColour(angle > angle18 ? Colours::orange : Colours::black);
	g.drawLine(l18, 2);
	g.setColour(angle > angle19 ? Colours::orange : Colours::black);
	g.drawLine(l19, 2);
	g.setColour(angle > angle20 ? Colours::orange : Colours::black);
	g.drawLine(l20, 2);
	g.setColour(angle > angle21 ? Colours::orange : Colours::black);
	g.drawLine(l21, 2);
	g.setColour(angle == angle22 ? Colours::orange : Colours::black);
	g.drawLine(l22, 2);
#pragma endregion


	g.setColour(slider.findColour(Slider::rotarySliderFillColourId));

	{
		Rectangle<float> bgBottom = r.reduced(7.0f);
		Path bnob;
		bnob.addRoundedRectangle(bgBottom, radius);
		g.fillPath(bnob);
		/*Path filledArc;
		filledArc.addPieSegment(r, rotaryStartAngle, angle, 0.0);

		g.fillPath(filledArc);*/
	}

	g.setColour(Colour(10, 10, 10));

	Rectangle<float> bgBottom = r.reduced(12.0f);
	Path bnob;
	bnob.addRoundedRectangle(bgBottom, radius);
	g.fillPath(bnob);
	g.setColour(Colour(80, 80, 80));

	Path knob;
	Rectangle<float> bgMiddle = r.reduced(20.0f);

	knob.addRoundedRectangle(bgMiddle, radius);
	g.fillPath(knob, t);

	Path needle;
	Rectangle<float> r2(bgMiddle * 0.125f);
	needle.addRoundedRectangle(r2.withPosition(Point<float>((bgMiddle.getCentreX() - (r2.getWidth() / 2.0f)), bgMiddle.getY() + 7)), r2.getWidth());

	g.setColour(Colour(245, 160, 32));
	g.fillPath(needle, AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));


	Rectangle<float> top(x, y, width, height);
	AttributedString s;
	s.setJustification(Justification::centredTop);
	s.setWordWrap(AttributedString::none);
	Font f;
	s.setFont(f);
	s.append(slider.getName());
	s.setColour(Colours::white);
	s.draw(g, top);

	Rectangle<float> area(m);
	area.removeFromBottom(-3);

	s.clear();
	s.setJustification(Justification::centredBottom);
	s.setWordWrap(AttributedString::none);

	s.append(slider.getComponentID());
	s.setColour(Colours::white);
	s.draw(g, area);

	area.removeFromLeft(15);
	area.removeFromBottom(-3);

	s.clear();
	s.setJustification(Justification::bottomLeft);
	s.setWordWrap(AttributedString::none);
	s.append(String(slider.getMinimum()));
	s.setColour(Colours::white);
	//s.setFont(font);
	s.draw(g, area);
	s.clear();

	s.setJustification(Justification::bottomRight);
	s.setWordWrap(AttributedString::none);
	double max = slider.getMaximum();

	s.append(String(max));
	s.setColour(isEnabled?Colours::white:Colours::grey);
	s.draw(g, area);



}
class LAFDialsStyle::SliderLabelComp : public Label
{
public:
	SliderLabelComp() : Label(String::empty, String::empty) {}

	void mouseWheelMove(const MouseEvent&, const MouseWheelDetails&) {}
};
Label* LAFDialsStyle::createSliderTextBox(Slider& slider)
{
	Label* const l = new SliderLabelComp();

	l->setJustificationType(Justification::centred);
	l->setKeyboardType(TextInputTarget::decimalKeyboard);

	l->setColour(Label::textColourId, slider.findColour(Slider::textBoxTextColourId));
	l->setColour(Label::backgroundColourId,
		(slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
		? Colours::transparentBlack
		: slider.findColour(Slider::textBoxBackgroundColourId));
	l->setColour(Label::outlineColourId, slider.findColour(Slider::textBoxOutlineColourId));
	l->setColour(TextEditor::textColourId, slider.findColour(Slider::textBoxTextColourId));
	l->setColour(TextEditor::backgroundColourId,
		slider.findColour(Slider::textBoxBackgroundColourId)
		.withAlpha((slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
			? 0.7f : 1.0f));
	l->setColour(TextEditor::outlineColourId, slider.findColour(Slider::textBoxOutlineColourId));
	l->setColour(TextEditor::highlightColourId, slider.findColour(Slider::textBoxHighlightColourId));

	return l;
}


LAFRadio::LAFRadio()
{
}

LAFRadio::~LAFRadio()
{
}

void LAFRadio::drawToggleButton(Graphics &g, ToggleButton &button, bool isMouseOverButton, bool isButtonDown)
{
	Colour baseColor = button.getToggleState() ? Colours::red : Colours::blue;
	if (button.hasKeyboardFocus(true))
	{
		baseColor = Colours::orange;
	}
		g.setColour(baseColor);
		g.drawVerticalLine(0,0,button.getHeight());//(0, 0, button.getWidth(), button.getHeight());
	float fontSize = jmin(15.0f, button.getHeight() * 0.75f);
	const float tickWidth = fontSize * 1.1f;

	//drawTickBox(g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
	//	tickWidth, tickWidth,
	//	button.getToggleState(),
	//	button.isEnabled(),
	//	isMouseOverButton,
	//	isButtonDown);

	g.setColour(baseColor);
	g.setFont(fontSize);

	if (!button.isEnabled())
		g.setOpacity(0.5f);

	const int textX = (int)tickWidth + 5;

	g.drawFittedText(button.getButtonText(),
		textX, 0,
		button.getWidth() - textX - 2, button.getHeight(),
		Justification::centredLeft, 10);
}

LAFToggleSwitch::LAFToggleSwitch()
{
}

LAFToggleSwitch::~LAFToggleSwitch()
{
}

void LAFToggleSwitch::drawToggleButton(Graphics & g, ToggleButton & button, bool isMouseOverButton, bool isButtonDown)
{
	Colour baseColor = button.getToggleState() ? Colours::red : Colours::blue;
	/*if (button.hasKeyboardFocus(true))
	{
		baseColor = Colours::orange;
	}*/
	juce::Rectangle<float> area(button.getLocalBounds().toFloat().reduced(2.0f));


	g.setColour(Colours::orange);
	g.fillRoundedRectangle(area, 20);
	
	g.setColour(Colours::green);
	float fontSize = jmin(15.0f, button.getHeight() * 0.75f);
	const float tickWidth = fontSize * 1.1f;
	g.setColour(baseColor);
		g.setFont(fontSize);

		if (!button.isEnabled())
			g.setOpacity(0.5f);

		const int textX = (int)tickWidth + 5;
	if (button.getToggleState())
	{
		juce::Rectangle<float> area1(area.removeFromLeft(area.getWidth() / 2));
		g.fillRoundedRectangle(area1, 20);
	
		g.setColour(Colours::white);
		g.drawFittedText(button.getName(),
			area1.getX()+10, 0,
			area1.getWidth() - textX - 2, area1.getHeight(),
			Justification::centredLeft, 10);
	}
	else
	{
		juce::Rectangle<float> area1(area.removeFromRight(area.getWidth() / 2));
		g.fillRoundedRectangle(area1, 20);
		g.setColour(Colours::white);
		g.drawFittedText(button.getButtonText(),
			area1.getX()+10, 0,
			area1.getWidth() - textX - 2, area1.getHeight(),
			Justification::centredLeft, 10);
	}	
}
