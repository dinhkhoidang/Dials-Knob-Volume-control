/*
  ==============================================================================

    LAFDials.h
    Created: 1 Jun 2016 11:38:08am
    Author:  khoi.dang

  ==============================================================================
*/

#ifndef LAFDIALS_H_INCLUDED
#define LAFDIALS_H_INCLUDED
#include "JuceHeader.h"
struct CustomLookAndFeel : public LookAndFeel_V3
{
	void drawRoundThumb(Graphics& g, const float x, const float y,
		const float diameter, const Colour& colour, float outlineThickness)
	{
		const Rectangle<float> a(x, y, diameter, diameter);
		const float halfThickness = outlineThickness * 0.5f;

		Path p;
		p.addEllipse(x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);

		const DropShadow ds(Colours::black, 1, Point<int>(0, 0));
		ds.drawForPath(g, p);

		g.setColour(colour);
		g.fillPath(p);

		g.setColour(colour.brighter());
		g.strokePath(p, PathStrokeType(outlineThickness));
	}

	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown) override
	{
		//button.setEnabled(false);
		Colour baseColour(backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
			.withMultipliedAlpha(button.isEnabled() ? 0.9f : 0.5f));

		if (isButtonDown || isMouseOverButton)
			baseColour = baseColour.contrasting(isButtonDown ? 0.5f : 0.1f);

		const bool flatOnLeft = button.isConnectedOnLeft();
		const bool flatOnRight = button.isConnectedOnRight();
		const bool flatOnTop = button.isConnectedOnTop();
		const bool flatOnBottom = button.isConnectedOnBottom();

		const float width = button.getWidth() - 1.0f;
		const float height = button.getHeight() - 1.0f;

		if (width > 0 && height > 0)
		{
			const float cornerSize = jmin(15.0f, jmin(width, height) * 0.45f);
			const float lineThickness = cornerSize * 0.1f;
			const float halfThickness = lineThickness * 0.5f;

			Path outline;
			outline.addRoundedRectangle(0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
				cornerSize, cornerSize,
				!(flatOnLeft || flatOnTop),
				!(flatOnRight || flatOnTop),
				!(flatOnLeft || flatOnBottom),
				!(flatOnRight || flatOnBottom));

			const Colour outlineColour(button.findColour(button.getToggleState() ? TextButton::textColourOnId
				: TextButton::textColourOffId));

			g.setColour(baseColour);
			g.fillPath(outline);

			if (!button.getToggleState())
			{
				g.setColour(outlineColour);
				g.strokePath(outline, PathStrokeType(lineThickness));
			}
		}
	}

	void drawTickBox(Graphics& g, Component& component,
		float x, float y, float w, float h,
		bool ticked,
		bool isEnabled,
		bool isMouseOverButton,
		bool isButtonDown) override
	{
		const float boxSize = w * 0.7f;

		bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
		const Colour colour(component.findColour(TextButton::buttonColourId).withMultipliedSaturation((component.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
			.withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.7f));

		drawRoundThumb(g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
			isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);

		if (ticked)
		{
			const Path tick(LookAndFeel_V2::getTickShape(6.0f));
			g.setColour(isEnabled ? findColour(TextButton::buttonOnColourId) : Colours::grey);

			const float scale = 9.0f;
			const AffineTransform trans(AffineTransform::scale(w / scale, h / scale)
				.translated(x - 2.5f, y + 1.0f));
			g.fillPath(tick, trans);
		}
	}

	void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) override
	{
		const float sliderRadius = (float)(getSliderThumbRadius(slider) - 2);

		bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
		Colour knobColour(slider.findColour(Slider::thumbColourId).withMultipliedSaturation((slider.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
			.withMultipliedAlpha(slider.isEnabled() ? 1.0f : 0.7f));

		if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
		{
			float kx, ky;

			if (style == Slider::LinearVertical)
			{
				kx = x + width * 0.5f;
				ky = sliderPos;
			}
			else
			{
				kx = sliderPos;
				ky = y + height * 0.5f;
			}

			const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

			drawRoundThumb(g,
				kx - sliderRadius,
				ky - sliderRadius,
				sliderRadius * 2.0f,
				knobColour, outlineThickness);
		}
		else
		{
			// Just call the base class for the demo
			LookAndFeel_V2::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
		}
	}

	void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) override
	{
		g.fillAll(slider.findColour(Slider::backgroundColourId));

		if (style == Slider::LinearBar || style == Slider::LinearBarVertical)
		{
			const float fx = (float)x, fy = (float)y, fw = (float)width, fh = (float)height;

			Path p;

			if (style == Slider::LinearBarVertical)
				p.addRectangle(fx, sliderPos, fw, 1.0f + fh - sliderPos);
			else
				p.addRectangle(fx, fy, sliderPos - fx, fh);


			Colour baseColour(slider.findColour(Slider::rotarySliderFillColourId)
				.withMultipliedSaturation(slider.isEnabled() ? 1.0f : 0.5f)
				.withMultipliedAlpha(0.8f));

			g.setColour(baseColour);
			g.fillPath(p);

			const float lineThickness = jmin(15.0f, jmin(width, height) * 0.45f) * 0.1f;
			g.drawRect(slider.getLocalBounds().toFloat(), lineThickness);
		}
		else
		{
			drawLinearSliderBackground(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
			drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
		}
	}

	void drawLinearSliderBackground(Graphics& g, int x, int y, int width, int height,
		float /*sliderPos*/,
		float /*minSliderPos*/,
		float /*maxSliderPos*/,
		const Slider::SliderStyle /*style*/, Slider& slider) override
	{
		const float sliderRadius = getSliderThumbRadius(slider) - 5.0f;
		Path on, off;

		if (slider.isHorizontal())
		{
			const float iy = y + height * 0.5f - sliderRadius * 0.5f;
			Rectangle<float> r(x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
			const float onW = r.getWidth() * ((float)slider.valueToProportionOfLength(slider.getValue()));

			on.addRectangle(r.removeFromLeft(onW));
			off.addRectangle(r);
		}
		else
		{
			const float ix = x + width * 0.5f - sliderRadius * 0.5f;
			Rectangle<float> r(ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
			const float onH = r.getHeight() * ((float)slider.valueToProportionOfLength(slider.getValue()));

			on.addRectangle(r.removeFromBottom(onH));
			off.addRectangle(r);
		}

		g.setColour(slider.findColour(Slider::rotarySliderFillColourId));
		g.fillPath(on);

		g.setColour(slider.findColour(Slider::trackColourId));
		g.fillPath(off);
	}

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
	{
		const float radius = jmin(width / 2, height / 2) - 2.0f;
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;
		const float rw = radius * 2.0f;
		const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		const float step = 1.0f/21.0f;
		const float angle1 = rotaryStartAngle + 0 * (rotaryEndAngle - rotaryStartAngle);
		
		
		Line<float> l1(centreX, ry, centreX, centreY);
	
		
		l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2);
		l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2);
		l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2);
		l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2);
		l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2);
		l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2);
		l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2); l1.applyTransform(AffineTransform::rotation(angle1, centreX, centreY));
		g.drawLine(l1, 2);

		
	}
};

//==============================================================================
/** Another really simple look and feel that is very flat and square.
This inherits from CustomLookAndFeel above for the linear bar and slider backgrounds.
*/
struct SquareLookAndFeel : public CustomLookAndFeel
{
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown) override
	{
		//button.setEnabled(false);
		Colour baseColour(backgroundColour.withMultipliedSaturation(button.hasKeyboardFocus(true) ? 1.3f : 0.9f)
			.withMultipliedAlpha(button.isEnabled() ? 0.9f : 0.5f));
		baseColour = (button.isEnabled() ? Colours::orange : Colours::black);
		if (isButtonDown || isMouseOverButton) {
			baseColour = (isButtonDown ? Colours::blue : Colours::red);
		}


		const float width = button.getWidth() - 1.0f;
		const float height = button.getHeight() - 1.0f;

		if (width > 0 && height > 0)
		{
			g.setColour((button.getToggleState() ? Colours::white : Colours::black));

			g.setGradientFill(ColourGradient(baseColour, 0.0f, 0.0f,
				baseColour.darker(0.1f), 0.0f, height, false));
			//g.drawText(button.getButtonText(), 0.5f, NotificationType::dontSendNotification, true);
			//g.set
			g.fillRect(button.getLocalBounds());
		}
	}

	void drawTickBox(Graphics& g, Component& component,
		float x, float y, float w, float h,
		bool ticked,
		bool isEnabled,
		bool /*isMouseOverButton*/,
		bool /*isButtonDown*/) override
	{
		const float boxSize = w * 0.7f;

		bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
		const Colour colour(component.findColour(TextButton::buttonOnColourId).withMultipliedSaturation((component.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
			.withMultipliedAlpha(component.isEnabled() ? 1.0f : 0.7f));
		g.setColour(colour);

		Rectangle<float> r(x, y + (h - boxSize) * 0.5f, boxSize, boxSize);
		g.fillRect(r);

		if (ticked)
		{
			const Path tick(LookAndFeel_V3::getTickShape(6.0f));
			g.setColour(isEnabled ? findColour(TextButton::buttonColourId) : Colours::grey);

			const AffineTransform trans(RectanglePlacement(RectanglePlacement::centred)
				.getTransformToFit(tick.getBounds(), r.reduced(r.getHeight() * 0.05f)));
			g.fillPath(tick, trans);
		}
	}

	void drawLinearSliderThumb(Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) override
	{
		const float sliderRadius = (float)getSliderThumbRadius(slider);

		bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
		Colour knobColour(slider.findColour(Slider::rotarySliderFillColourId).withMultipliedSaturation((slider.hasKeyboardFocus(false) || isDownOrDragging) ? 1.3f : 0.9f)
			.withMultipliedAlpha(slider.isEnabled() ? 1.0f : 0.7f));
		g.setColour(knobColour);

		if (style == Slider::LinearHorizontal || style == Slider::LinearVertical)
		{
			float kx, ky;

			if (style == Slider::LinearVertical)
			{
				kx = x + width * 0.5f;
				ky = sliderPos;
				g.fillRect(Rectangle<float>(kx - sliderRadius, ky - 2.5f, sliderRadius * 2.0f, 5.0f));
			}
			else
			{
				kx = sliderPos;
				ky = y + height * 0.5f;
				g.fillRect(Rectangle<float>(kx - 2.5f, ky - sliderRadius, 5.0f, sliderRadius * 2.0f));
			}
		}
		else
		{
			// Just call the base class for the demo
			LookAndFeel_V2::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
		}
	}

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
	{
		const float diameter = jmin(width, height) +5.0f;
		const float radius = (diameter / 2.0f) * std::cos(float_Pi / 4.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;
		const float rw = radius * 2.0f;
		const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

		const Colour baseColour(slider.isEnabled() ? slider.findColour(Slider::rotarySliderFillColourId).withAlpha(isMouseOver ? 0.8f : 1.0f)
			: Colour(0x80808080));
		Rectangle<float> b(x, y, width, height);
		g.fillRect(b);
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
		g.setColour(angle > angle6? Colours::orange : Colours::black);
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
		g.setColour(angle > angle17? Colours::orange : Colours::black);
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
		needle.addRoundedRectangle(r2.withPosition(Point<float>((bgMiddle.getCentreX() - (r2.getWidth() / 2.0f)), bgMiddle.getY()+7)), r2.getWidth());

		g.setColour(Colour(245, 160, 32));
		g.fillPath(needle, AffineTransform::rotation(angle, r.getCentreX(), r.getCentreY()));

	
		Rectangle<float> top(x,y,width,height);
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
		s.setColour(Colours::white);
		s.draw(g, area);

		
	
	}
	//==============================================================================
	
};

class LAFDialsStyle: public LookAndFeel_V2
{
public:
	LAFDialsStyle();
	LAFDialsStyle(Slider* slider,Colour brColor,String title,String dv);
	~LAFDialsStyle();
	Slider::SliderLayout getSliderLayout(Slider& slider) override;
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
	Label* createSliderTextBox(Slider& slider) override;
	

private:
	class SliderLabelComp;
	
};


class LAFRadio :public LookAndFeel_V2
{
public:
	LAFRadio();
	~LAFRadio();
	void drawToggleButton(Graphics&, ToggleButton&, bool isMouseOverButton, bool isButtonDown) override;
private:

};

class LAFToggleSwitch :public LookAndFeel_V2
{
public:
	LAFToggleSwitch();
	~LAFToggleSwitch();
	void drawToggleButton(Graphics&, ToggleButton&, bool isMouseOverButton, bool isButtonDown) override;
private:

};


#endif  // LAFDIALS_H_INCLUDED
