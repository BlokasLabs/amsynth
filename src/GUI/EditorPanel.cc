/* amSynth
 * (c) 2003 Nick Dowell
 */

#include "EditorPanel.h"

#include "../Preset.h"
#include "ParameterKnob.h"
#include "ParameterSwitch.h"
#include "RadioButtonParameterView.h"

#include "knob.xpm"

EditorPanel::EditorPanel	( VoiceAllocationUnit* vau, 
					Preset* preset, int piped )
{
	
	// GUI::GUI()
	
	style = Gtk::Style::create ( );
	
	
	GtkShadowType frame_shadow = GTK_SHADOW_OUT;
	
	
	
	for (int i = 0; i < 31; i++)
		parameterView[i] = new ParameterKnob( piped );
	for (int i = 0; i < 10; i++)
		rb_pv[i] = new RadioButtonParameterView( piped );
	
	param_switch = new ParameterSwitch( piped );
	
	
	
	
	
	// oscillator 1 controls
	osc1_frame.set_shadow_type( frame_shadow );
	osc1_frame.set_label( "Oscillator 1" );
	osc1_fixed.put( *rb_pv[0], 0, 0 );		// waveform
	osc1_fixed.put( *parameterView[18], 10, 135 );	// pulsewidth
	osc1_frame.add( osc1_fixed );

	// oscillator 2 controls
	osc2_frame.set_shadow_type( frame_shadow );
	osc2_frame.set_label( "Oscillator 2" );
	osc2_fixed.put( *param_switch, 85, 0 );		// osc. sync
	osc2_fixed.put( *rb_pv[1], 10, 0 );		// waveform
	osc2_fixed.put( *parameterView[1], 150, 70 );	// pulsewidth
	osc2_fixed.put( *rb_pv[2], 85, 30 );		// octave
	osc2_fixed.put( *parameterView[3], 150, 0 );	// detune
	osc2_frame.add( osc2_fixed );

	// oscillator mixer section
	osc_mix_frame.set_shadow_type(frame_shadow);
	osc_mix_frame.set_label("Oscillator Mixer");
	osc_mix_vbox.add(*parameterView[4]);
	osc_mix_vbox.add(*rb_pv[3]);
	osc_mix_frame.add(osc_mix_vbox);

	// filter controls
	filter_frame.set_shadow_type(frame_shadow);
	filter_frame.set_label("Low Pass Filter");
	filter_hbox1.add(*parameterView[6]);
	filter_hbox1.add(*parameterView[7]);
	filter_hbox1.add(*parameterView[5]);
    	filter_hbox2.add(*parameterView[8]);
	filter_hbox2.add(*parameterView[9]);
	filter_hbox2.add(*parameterView[10]);
	filter_hbox2.add(*parameterView[11]);
	filter_vbox.add(filter_hbox1);
	filter_vbox.add(filter_hbox2);
	filter_frame.add(filter_vbox);

	// amplifier controls
	amp_frame.set_shadow_type(frame_shadow);
	amp_frame.set_label("Amplifier");
	amp_hbox2.add(*parameterView[13]);
	amp_hbox2.add(*parameterView[14]);
	amp_hbox2.add(*parameterView[15]);
	amp_hbox2.add(*parameterView[16]);
	amp_vbox.add(amp_hbox2);
	amp_frame.add(amp_vbox);

	// mod controls
	mod_frame.set_shadow_type( frame_shadow );
	mod_frame.set_label( "Modulation" );
	mod_frame.add( mod_hbox );
	mod_hbox.add( *parameterView[20] );		// lfo rate
	mod_hbox.add( *rb_pv[4] );			// waveform switch
	mod_hbox.add( *parameterView[22] );		// freq mod
	mod_hbox.add( *parameterView[12] );		// filter mod
	mod_hbox.add( *parameterView[17] );		// amp mod

	// reverb :)) section
	reverb_frame.set_shadow_type( frame_shadow );
	reverb_frame.set_label( "Reverb" );
	reverb_hbox.add( *parameterView[24] );		// amount
	reverb_hbox.add( *parameterView[23] );		// room size
	reverb_hbox.add( *parameterView[26] );		// width
	reverb_hbox.add( *parameterView[28] );		// damping
	reverb_frame.add( reverb_hbox );

	// distortion section
	distortion_frame.set_shadow_type(frame_shadow);
	distortion_frame.set_label("Distortion");
	distortion_hbox.add(*parameterView[30]);
	distortion_frame.add(distortion_hbox);

	// the main panel
	put(osc1_frame, 0, 0);
	put(osc2_frame, 0, 0);
	put(osc_mix_frame, 0, 0);
	put(filter_frame, 0, 0);
	put(amp_frame, 0, 0);
	put(mod_frame, 0, 0);
	put(reverb_frame, 0, 0);
	put( *parameterView[19], 0, 0 );
	put(distortion_frame, 0, 0);
	
	
	
	
	
	
	// GUI::init()
	
	
	
	
	/*
	 * connect all the controls to their respective parameters.
	 * this is not done in the constructor since we must have been given
	 * the PresetController first..
	 */

	// controls for oscillator 1
	parameterView[18]->setParameter(preset->getParameter("osc1_pulsewidth"));
	parameterView[18]->drawValue( false );
	parameterView[18]->setName( "Pulsewidth" );
	
	rb_pv[0]->setParameter(preset->getParameter("osc1_waveform"));
	rb_pv[0]->setName("waveform");
	rb_pv[0]->setDescription(0, "random");
	rb_pv[0]->setDescription(1, "noise");
	rb_pv[0]->setDescription(2, "saw");
	rb_pv[0]->setDescription(3, "square");
	rb_pv[0]->setDescription(4, "sine");
	
	// controls for oscillator 2
	parameterView[1]->setParameter(preset->getParameter("osc2_pulsewidth"));
	parameterView[1]->drawValue( false );
	parameterView[1]->setName( "Pulsewidth" );
	
	rb_pv[1]->setParameter(preset->getParameter("osc2_waveform"));
	rb_pv[1]->setName("Waveform");
	rb_pv[1]->setDescription(0, "random");
	rb_pv[1]->setDescription(1, "noise");
	rb_pv[1]->setDescription(2, "saw");
	rb_pv[1]->setDescription(3, "square");
	rb_pv[1]->setDescription(4, "sine");
	rb_pv[2]->setParameter(preset->getParameter("osc2_range"));
	rb_pv[2]->setName("octave");
	rb_pv[2]->setDescription(0, "+2");
	rb_pv[2]->setDescription(1, "+1");
	rb_pv[2]->setDescription(2, "0");
	rb_pv[2]->setDescription(3, "-1");
	parameterView[3]->setParameter(preset->getParameter("osc2_detune"));
	parameterView[3]->setName( "Detune" );
	parameterView[3]->drawValue( false );

	//
	// oscillator mixer section controls
	//
	parameterView[4]->setParameter(preset->getParameter("osc_mix"));
	parameterView[4]->drawValue( false );
	parameterView[4]->setName("osc1  -  osc2");
	rb_pv[3]->setParameter(preset->getParameter("osc_mix_mode"));
	rb_pv[3]->setName("Mix mode");
	rb_pv[3]->setDescription(0, "ring mod");
	rb_pv[3]->setDescription(1, "normal");

	//
	// filter controls
	//
	parameterView[5]->setParameter(preset->getParameter("filter_env_amount"));
	parameterView[5]->setName( "Env.\nAmount" );
	parameterView[6]->setParameter(preset->getParameter("filter_cutoff"));
	parameterView[6]->setName( "Cutoff\nFreq." );
	parameterView[6]->drawValue( false );
	parameterView[7]->setParameter(preset->getParameter("filter_resonance"));
	parameterView[7]->setName( "\nResonance" );
	parameterView[7]->drawValue( false );
	parameterView[8]->setParameter(preset->getParameter("filter_attack"));
	parameterView[8]->setName( "Attack" );
	parameterView[8]->drawValue( true );
	parameterView[9]->setParameter(preset->getParameter("filter_decay"));
	parameterView[9]->setName( "Decay" );
	parameterView[9]->drawValue( true );
	parameterView[10]->setParameter(preset->getParameter("filter_sustain"));
	parameterView[10]->setName( "Sustain" );
	parameterView[10]->drawValue( true );
	parameterView[11]->setParameter(preset->getParameter("filter_release"));
	parameterView[11]->setName( "Release" );
	parameterView[11]->drawValue( true );
	parameterView[12]->setParameter(preset->getParameter("filter_mod_amount"));
	parameterView[12]->setName( "Filter\nMod.\nAmount" );
	parameterView[12]->drawValue( false );


	//
	// voice amplitude
	//
	parameterView[13]->setParameter(preset->getParameter("amp_attack"));
	parameterView[13]->setName( "Attack" );
	parameterView[13]->drawValue( true );
	parameterView[14]->setParameter(preset->getParameter("amp_decay"));
	parameterView[14]->setName( "Decay" );
	parameterView[14]->drawValue( true );
	parameterView[15]->setParameter(preset->getParameter("amp_sustain"));
	parameterView[15]->setName( "Sustain" );
	parameterView[15]->drawValue( true );
	parameterView[16]->setParameter(preset->getParameter("amp_release"));
	parameterView[16]->setName( "Release" );
	parameterView[16]->drawValue( true );
	parameterView[17]->setParameter(preset->getParameter("amp_mod_amount"));
	parameterView[17]->setName( "Amplitude\nMod.\nAmount" );
	parameterView[17]->drawValue( false );
	/* 18 is taken */
	parameterView[19]->setParameter(preset->getParameter("master_vol"));
	parameterView[19]->setName( "Master Vol." );

	//
	// mod section
	//
	parameterView[20]->setParameter(preset->getParameter("lfo_freq"));
	parameterView[20]->drawValue( true );
	parameterView[20]->setName( "Rate" );
	rb_pv[4]->setParameter(preset->getParameter("lfo_waveform"));
	rb_pv[4]->setName("waveform");
	rb_pv[4]->setDescription(0, "random");
	rb_pv[4]->setDescription(1, "noise");
	rb_pv[4]->setDescription(2, "saw");
	rb_pv[4]->setDescription(3, "square");
	rb_pv[4]->setDescription(4, "sine");

	//
	// freq control section
	//
	parameterView[22]->setParameter(preset->getParameter("freq_mod_amount"));
	parameterView[22]->setName( "Frequency\nMod.\nAmount" );
	parameterView[22]->drawValue( false );

	//
	// reverb control section
	//
	parameterView[23]->setParameter(preset->getParameter("reverb_roomsize"));
	parameterView[23]->setName( "Room\nSize" );
	parameterView[24]->setParameter(preset->getParameter("reverb_wet"));
	parameterView[24]->setName( "\nAmount" );
	parameterView[26]->setParameter(preset->getParameter("reverb_width"));
	parameterView[26]->setName( "Stereo\nWidth" );
	parameterView[28]->setParameter(preset->getParameter("reverb_damp"));
	parameterView[28]->setName( "\nDamping" );

	//
	// distortion control section
	//
	parameterView[30]->setParameter(preset->getParameter("distortion_crunch"));
	parameterView[30]->setName( "Crunch" );
	
	param_switch->setParameter(preset->getParameter("osc2_sync"));
	param_switch->setName( "Sync. to\nOsc. 1" );
}

EditorPanel::~EditorPanel	( )
{
}

void
EditorPanel::set_x_font		( const char *x_font_desc )
{
	// apply font to current style.
	Gdk_Font font = style->get_font ( );
	font.load ( x_font_desc );
	style->set_font ( font );
	

	for (int i = 0; i < 31; i++)
	{
		parameterView[i]->set_style ( *style );
		parameterView[i]->queue_resize ( );
	}
	for (int i = 0; i < 10; i++)
	{
		rb_pv[i]->set_style ( *style );
		rb_pv[i]->queue_resize ( );
	}
	param_switch->set_style ( *style );
	param_switch->queue_resize ( );
	
	osc1_frame.set_style ( *style );
	osc1_frame.queue_resize ( );
	osc2_frame.set_style ( *style );
	osc2_frame.queue_resize ( );
	osc_mix_frame.set_style ( *style );
	osc_mix_frame.queue_resize ( );
	reverb_frame.set_style ( *style );
	reverb_frame.queue_resize ( );
	distortion_frame.set_style ( *style );
	distortion_frame.queue_resize ( );
	filter_frame.set_style ( *style );
	filter_frame.queue_resize ( );
	amp_frame.set_style ( *style );
	amp_frame.queue_resize ( );
	mod_frame.set_style ( *style );
	mod_frame.queue_resize ( );
	queue_resize ( );
}

void
EditorPanel::arrange		( )
{
	gint x, y;
	x = 10;
	y = 5;
	move( osc1_frame, x, y );
	y += 220;
	move( osc2_frame, x, y );
	x += 75;
	y += 80;
	move( osc_mix_frame, x, 5 );
	move( mod_frame, 240, y-80 );
	move( distortion_frame, 530, y-80 );
	x = 175;
	y = 5;
	move( filter_frame, x, y );
	x += 210;
	move( amp_frame, x, y );
	y += 100;
	move( reverb_frame, x, y );
	resize_children();
	move( *parameterView[19], 530, 305);		// master vol.
}

void
EditorPanel::realize_impl	( )
{
	Gtk::Fixed::realize_impl();
	
	GdkPixmap *pixmap;
	GdkBitmap *bitmap;

	pixmap = gdk_pixmap_create_from_xpm_d(get_window(), &bitmap,
			get_style()->gtkobj()->bg, knob_xpm);

	for(int i=0; i < 31; i++)
		parameterView[i]->setPixmap( pixmap, 50, 50, 15 );
}