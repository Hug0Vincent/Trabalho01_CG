#include "addobject.h"

AddObject::AddObject(Facade &facade) :
      facade(facade),
      m_vbox(Gtk::ORIENTATION_VERTICAL),
      button_close("Close"),
      button_save_line("Save Line"),
      button_save_wire("Save Polygon"),
      button_save_point("Save Point"),
      button_save_bspline("Save B-Spline"),
      button_add_coordenate("Add Coordenate"),
	  button_save_object3d("Save Object 3D"),
	  button_add_line3d("Add Line 3D"),
      insert_border_color_label("Insert a RGB border color : "),
      insert_filling_color_label("Insert a RGB filling color : "),
      insert_a_coordinate_label("Insert a Coordinate : "),
      point_x_label("Coordinate X : "),
      point_y_label("Coordinate Y : "),
      line_x1_label("Coordinate X1 : "),
      line_y1_label("Coordinate Y1 : "),
      line_x2_label("Coordinate X2 : "),
      line_y2_label("Coordinate Y2 : "),
      polygon_x_label("Coordinate X : "),
      polygon_y_label("Coordinate Y : "),
      bspline_x_label("Coordinate X : "),
      bspline_y_label("Coordinate Y : "),

	  button_add_vector("Add Vector"),
      button_add_vector_bspline("Add Vector"),
	  button_save_curve("Save Curve"),
      curve_x1_label("Vector X1: "),
	  curve_x2_label("Vector X2: "),
	  curve_y1_label("Vector Y1: "),
	  curve_y2_label("Vector Y2: "),
	  info_curve_label("Insert a Vector:"),

	  object3d_x1_label("Coordinate X\u2081: "),
	  object3d_y1_label("Coordinate Y\u2081: "),
	  object3d_x2_label("Coordinate X\u2082: "),
	  object3d_y2_label("Coordinate Y\u2082: "),
	  object3d_z1_label("Coordinate Z\u2081: "),
	  object3d_z2_label("Coordinate Z\u2082: "),
	  info_object3d_label("Insert a Line:"),

      liang_barsky_radiobutton("Liang-Barsky"),
      cohen_sutheland_radiobutton("Cohen-Sutheland")

{
  LOG(2, "Entering...");
  this->on_liang_radiobutton();

  insert_border_color_field_r.set_text("0");
  insert_border_color_field_g.set_text("0");
  insert_border_color_field_b.set_text("0");
  insert_filling_color_field_r.set_text("0");
  insert_filling_color_field_g.set_text("0");
  insert_filling_color_field_b.set_text("0");
  color_grid.attach(insert_border_color_label   , 1, 1, 1, 1);
  color_grid.attach(insert_border_color_field_r , 2, 1, 1, 1);
  color_grid.attach(insert_border_color_field_g , 3, 1, 1, 1);
  color_grid.attach(insert_border_color_field_b , 4, 1, 1, 1);
  color_grid.attach(insert_filling_color_label  , 1, 2, 1, 1);
  color_grid.attach(insert_filling_color_field_r, 2, 2, 1, 1);
  color_grid.attach(insert_filling_color_field_g, 3, 2, 1, 1);
  color_grid.attach(insert_filling_color_field_b, 4, 2, 1, 1);

  point_name_field.set_text("point1");
  point_name_field.set_placeholder_text("Name");
  point_x_field.set_text("50");
  point_y_field.set_text("50");
  point_grid.set_column_homogeneous(true);
  point_grid.set_row_spacing(10);
  point_grid.attach(point_name_field , 1, 1, 2, 1);
  point_grid.attach(point_x_label    , 1, 2, 1, 1);
  point_grid.attach(point_x_field    , 2, 2, 1, 1);
  point_grid.attach(point_y_label    , 1, 3, 1, 1);
  point_grid.attach(point_y_field    , 2, 3, 1, 1);
  point_grid.attach(button_save_point, 1, 4, 2, 1);

  liang_barsky_radiobutton.set_active();
  cohen_sutheland_radiobutton.join_group(liang_barsky_radiobutton);

  line_name_field.set_placeholder_text("Name");
  line_name_field.set_text("line1");
  line_x1_field.set_text("0");
  line_y1_field.set_text("0");
  line_x2_field.set_text("50");
  line_y2_field.set_text("50");
  line_grid.set_column_homogeneous(true);
  line_grid.set_row_spacing(10);
  line_grid.attach(line_name_field            , 1, 1, 2, 1);
  line_grid.attach(liang_barsky_radiobutton   , 3, 1, 1, 1);
  line_grid.attach(cohen_sutheland_radiobutton, 4, 1, 1, 1);
  line_grid.attach(line_x1_label              , 1, 2, 1, 1);
  line_grid.attach(line_x1_field              , 2, 2, 1, 1);
  line_grid.attach(line_x2_label              , 1, 3, 1, 1);
  line_grid.attach(line_x2_field              , 2, 3, 1, 1);
  line_grid.attach(line_y1_label              , 3, 2, 1, 1);
  line_grid.attach(line_y1_field              , 4, 2, 1, 1);
  line_grid.attach(line_y2_label              , 3, 3, 1, 1);
  line_grid.attach(line_y2_field              , 4, 3, 1, 1);
  line_grid.attach(button_save_line           , 1, 4, 4, 1);

  polygon_name_field.set_placeholder_text("Name");
  polygon_name_field.set_text("polygon1");
  wire_x_field.set_text("0");
  wire_y_field.set_text("0");
  polygn_grid.set_column_homogeneous(true);
  polygn_grid.set_row_spacing(10);
  polygn_grid.attach(polygon_name_field       , 1, 1, 1, 1);
  polygn_grid.attach(insert_a_coordinate_label, 2, 1, 1, 1);
  polygn_grid.attach(polygon_x_label          , 1, 2, 1, 1);
  polygn_grid.attach(wire_x_field             , 2, 2, 1, 1);
  polygn_grid.attach(polygon_y_label          , 1, 3, 1, 1);
  polygn_grid.attach(wire_y_field             , 2, 3, 1, 1);
  polygn_grid.attach(button_add_coordenate    , 1, 5, 1, 1);
  polygn_grid.attach(button_save_wire         , 2, 5, 1, 1);

  //bspline

  bspline_name_field.set_placeholder_text("Name");
  bspline_name_field.set_text("b-spline1");
  bspline_x_field.set_text("0");
  bspline_y_field.set_text("0");
  bspline_grid.set_column_homogeneous(true);
  bspline_grid.set_row_spacing(10);
  bspline_grid.attach(bspline_name_field       , 1, 1, 1, 1);
  bspline_grid.attach(info_bspline_label, 2, 1, 1, 1);
  bspline_grid.attach(bspline_x_label          , 1, 2, 1, 1);
  bspline_grid.attach(bspline_x_field             , 2, 2, 1, 1);
  bspline_grid.attach(bspline_y_label          , 1, 3, 1, 1);
  bspline_grid.attach(bspline_y_field             , 2, 3, 1, 1);
  bspline_grid.attach(button_add_vector_bspline    , 1, 5, 1, 1);
  bspline_grid.attach(button_save_bspline         , 2, 5, 1, 1);

  	//Add curve grid
	curve_grid.set_column_homogeneous(true);
	curve_grid.set_row_spacing(10);
	curve_grid.set_column_spacing(10);
	curve_name_field.set_placeholder_text("Name");
	curve_grid.attach(curve_name_field, 1, 1, 2, 1);
	curve_grid.attach(info_curve_label, 1, 2, 1, 1);
	curve_grid.attach(curve_x1_label, 1, 3, 1, 1);
	curve_grid.attach(curve_x1_field, 2, 3, 1, 1);
	curve_grid.attach(curve_x2_label, 1, 4, 1, 1);
	curve_grid.attach(curve_x2_field, 2, 4, 1, 1);
	curve_grid.attach(curve_y1_label, 3, 3, 1, 1);
	curve_grid.attach(curve_y1_field, 4, 3, 1, 1);
	curve_grid.attach(curve_y2_label, 3, 4, 1, 1);
	curve_grid.attach(curve_y2_field, 4, 4, 1, 1);

	curve_grid.attach(button_add_vector, 1, 5, 2, 1);
	curve_grid.attach(button_save_curve, 3, 5, 2, 1);
	curve_grid.set_border_width(10);

	//Add object3d grid
	object3d_grid.set_column_homogeneous(true);
	object3d_grid.set_row_spacing(10);
	object3d_grid.set_column_spacing(10);
	object3d_name_field.set_placeholder_text("Name");
	object3d_grid.attach(object3d_name_field, 1, 1, 2, 1);
	object3d_grid.attach(info_object3d_label, 3, 1, 2, 1);
	object3d_grid.attach(object3d_x1_label, 1, 2, 1, 1);
	object3d_grid.attach(object3d_x1_field, 2, 2, 1, 1);
	object3d_grid.attach(object3d_x2_label, 3, 2, 1, 1);
	object3d_grid.attach(object3d_x2_field, 4, 2, 1, 1);
	object3d_grid.attach(object3d_y1_label, 1, 3, 1, 1);
	object3d_grid.attach(object3d_y1_field, 2, 3, 1, 1);
	object3d_grid.attach(object3d_y2_label, 3, 3, 1, 1);
	object3d_grid.attach(object3d_y2_field, 4, 3, 1, 1);
	object3d_grid.attach(object3d_z1_label, 1, 4, 1, 1);
	object3d_grid.attach(object3d_z1_field, 2, 4, 1, 1);
	object3d_grid.attach(object3d_z2_label, 3, 4, 1, 1);
	object3d_grid.attach(object3d_z2_field, 4, 4, 1, 1);
	object3d_grid.attach(button_add_line3d, 1, 5, 2, 1);
	object3d_grid.attach(button_save_object3d, 3, 5, 2, 1);
	object3d_grid.set_border_width(10);

  button_close.signal_clicked().connect( sigc::mem_fun(*this, &AddObject::on_button_close) );
  button_save_point.signal_clicked().connect( sigc::mem_fun(*this, &AddObject::on_button_save_point) );
  button_save_line.signal_clicked().connect( sigc::mem_fun(*this, &AddObject::on_button_save_line) );
  button_add_coordenate.signal_clicked().connect( sigc::mem_fun(*this, &AddObject::on_button_add_coordinate) );
  button_save_wire.signal_clicked().connect( sigc::mem_fun(*this, &AddObject::on_button_save_polygon) );
  button_save_curve.signal_clicked().connect(sigc::mem_fun(*this, &AddObject::on_button_save_curve) );
  button_add_vector.signal_clicked().connect(sigc::mem_fun(*this, &AddObject::on_button_add_vector) );
  button_save_bspline.signal_clicked().connect(sigc::mem_fun(*this, &AddObject::on_button_save_bspline) );
  button_add_vector_bspline.signal_clicked().connect(sigc::mem_fun(*this, &AddObject::on_button_add_vector_bspline) );

  liang_barsky_radiobutton.signal_clicked().connect( sigc::mem_fun(*this, &AddObject::on_liang_radiobutton) );
  cohen_sutheland_radiobutton.signal_clicked().connect( sigc::mem_fun(*this, &AddObject::on_cohen_radiobutton) );

  button_add_line3d.signal_clicked().connect(sigc::mem_fun(*this, &AddObject::on_button_add_line3d) );
  button_save_object3d.signal_clicked().connect(sigc::mem_fun(*this, &AddObject::on_button_save_object3d) );

  m_notebook.set_border_width(0);
  m_vbox.pack_start(m_notebook);
  m_vbox.pack_start(color_grid, Gtk::PACK_SHRINK);
  m_vbox.pack_start(button_close, Gtk::PACK_EXPAND_WIDGET);

  m_notebook.append_page(point_grid, "Point");
  m_notebook.append_page(line_grid, "Line");
  m_notebook.append_page(polygn_grid, "Polygon");
  m_notebook.append_page(curve_grid, "Bezier Curve");
  m_notebook.append_page(bspline_grid, "B-Spline");
  m_notebook.append_page(object3d_grid, "Object 3D");

  this->window.set_title("Add Object");
  this->window.set_border_width(12);
  this->window.add(m_vbox);
  this->window.show_all_children();
}

AddObject::~AddObject()
{
}

Gtk::Window& AddObject::getWindow()
{
  return this->window;
}

void AddObject::on_button_save_point()
{
  std::string name = point_name_field.get_text().raw();
  LOG(4, "Name: %s", name);

  if (name.empty())
  {
    point_name_field.grab_focus();
    return;
  }

  std::string x_string = point_x_field.get_text().raw();
  std::string y_string = point_y_field.get_text().raw();

  int x_coord = atoi(x_string.c_str());
  int y_coord = atoi(y_string.c_str());

  Coordinate border = this->_get_rgb_color(insert_border_color_field_r, insert_border_color_field_g, insert_border_color_field_b);

  this->facade.addPoint(name, x_coord, y_coord, border);
  this->facade.queue_draw();

  this->window.close();
}

void AddObject::on_button_save_line()
{
  std::string name = line_name_field.get_text().raw();
  LOG(4, "Name: %s", name);

  if (name.empty())
  {
    line_name_field.grab_focus();
    return;
  }

  std::string x1_string = line_x1_field.get_text().raw();
  std::string y1_string = line_y1_field.get_text().raw();
  std::string x2_string = line_x2_field.get_text().raw();
  std::string y2_string = line_y2_field.get_text().raw();

  int x1_cord = atoi(x1_string.c_str());
  int y1_cord = atoi(y1_string.c_str());
  int x2_cord = atoi(x2_string.c_str());
  int y2_cord = atoi(y2_string.c_str());

  Coordinate border = this->_get_rgb_color(insert_border_color_field_r, insert_border_color_field_g, insert_border_color_field_b);

  this->facade.addLine(name, x1_cord, y1_cord, x2_cord, y2_cord, border, this->line_clipping_type);
  this->facade.queue_draw();

  this->window.close();
}

void AddObject::on_button_save_polygon()
{
  if (!polygon_coord_list.empty())
  {
    std::string name = polygon_name_field.get_text().raw();
    LOG(4, "Name: %s", name);

    if (name.empty())
    {
      polygon_name_field.grab_focus();
      return;
    }

    Coordinate border = this->_get_rgb_color(insert_border_color_field_r, insert_border_color_field_g, insert_border_color_field_b);
    Coordinate filling = this->_get_rgb_color(insert_filling_color_field_r, insert_filling_color_field_g, insert_filling_color_field_b);

    this->facade.addPolygon(name, polygon_coord_list, border, filling);
    this->facade.queue_draw();

    while(!polygon_coord_list.empty())
    {
      polygon_coord_list.pop_back();
    }

    this->window.close();
  }
  else
  {
    return ;
  }
}

void AddObject::on_button_add_coordinate()
{
  std::string x_string = wire_x_field.get_text().raw();
  std::string y_string = wire_y_field.get_text().raw();
  // std::string z_string = wire_z_field.get_text().raw();

  int x_coord = atoi(x_string.c_str());
  int y_coord = atoi(y_string.c_str());
  // int z_coord = atoi(z_string.c_str());

  polygon_coord_list.push_back(x_coord);
  polygon_coord_list.push_back(y_coord);
  // polygon_coord_list.push_back(z_coord);
  polygon_coord_list.push_back(1);

  wire_x_field.set_text("");
  wire_y_field.set_text("");

  std::string insert_a_coordinate_label_contents = "Added X : " + std::to_string(x_coord) + " Y : " + std::to_string(y_coord);

  LOG(4, insert_a_coordinate_label_contents.c_str());
  insert_a_coordinate_label.set_text(insert_a_coordinate_label_contents);
}

void AddObject::on_button_close()
{
  this->window.close();
}

Coordinate AddObject::_get_rgb_color(Gtk::Entry& field_r, Gtk::Entry& field_g, Gtk::Entry& field_b)
{
  big_double border_r{std::stold(field_r.get_text().raw().c_str())};
  big_double border_g{std::stold(field_g.get_text().raw().c_str())};
  big_double border_b{std::stold(field_b.get_text().raw().c_str())};
  Coordinate border = Coordinate(border_r, border_g, border_b);

  if( border < 0.0 || border > 1.0 )
  {
    LOG(1, "");
    LOG(1, "");
    LOG(1, "Error! Invalid RGB color passed for border or filling: %s", border);
    return Coordinate(0, 0, 0);
  }

  return border;
}

void AddObject::on_liang_radiobutton()
{
  this->line_clipping_type = LineClippingType::LIANG_BARSKY;
}

void AddObject::on_cohen_radiobutton()
{
  this->line_clipping_type = LineClippingType::COHEN_SUTHELAND;
}
void AddObject::on_button_add_vector(){

	std::string x1_string = curve_x1_field.get_text().raw();
	std::string y1_string = curve_y1_field.get_text().raw();
	std::string x2_string = curve_x2_field.get_text().raw();
	std::string y2_string = curve_y2_field.get_text().raw();
	int x1_cord = atoi(x1_string.c_str());
	int y1_cord = atoi(y1_string.c_str());
	int x2_cord = atoi(x2_string.c_str());
	int y2_cord = atoi(y2_string.c_str());

	Coordinate begin(x1_cord, y1_cord, 1);
	Coordinate end(x2_cord, y2_cord, 1);
	curve_vector_list.push_back(std::make_pair(begin, end));

	curve_x1_field.set_text("");
	curve_x2_field.set_text("");
	curve_y1_field.set_text("");
	curve_y2_field.set_text("");

	info_curve_label.set_text("Added X1 : " + std::to_string(x1_cord) +
	                      " Y1 : " + std::to_string(y1_cord) +
	                      " X2 : " + std::to_string(x2_cord) +
	                      " Y2 : " + std::to_string(y2_cord));

}

void AddObject::on_button_save_curve(){
	if (curve_vector_list.size() > 1)
	{
		std::string name = curve_name_field.get_text().raw();
		if (name.empty())
		{
			curve_name_field.grab_focus();
			return;
		}

		Coordinate border = this->_get_rgb_color(insert_border_color_field_r, insert_border_color_field_g, insert_border_color_field_b);

		this->facade.addCurveBezier(name, curve_vector_list, border);

		this->facade.queue_draw();


		while(!curve_vector_list.empty())
		{
			curve_vector_list.pop_back();
		}

		LOG(4,"A curve was added \n" );

		this->window.close();

	}
	else
	{
		info_curve_label.set_text("You need at least 2 vectors");
	}
}

void AddObject::on_button_save_bspline(){

  if (bspline_coord_list.size() > 3 )
	{
		std::string name = bspline_name_field.get_text().raw();
		if (name.empty())
		{
			bspline_name_field.grab_focus();
			return;
		}

		Coordinate border = this->_get_rgb_color(insert_border_color_field_r, insert_border_color_field_g, insert_border_color_field_b);

		this->facade.addBSpline(name, bspline_coord_list, border);

    LOG(4, "before draw");
		this->facade.queue_draw();


		while(!bspline_coord_list.empty())
		{
			bspline_coord_list.pop_back();
		}

		LOG(4,"A B-Spline was added \n" );

    std::string insert_a_coordinate_label_contents ="";
		this->window.close();

	}
	else
	{
		info_bspline_label.set_text("You need at least 4 points");
	}
	
}

void AddObject::on_button_add_vector_bspline(){

  std::string x_string = bspline_x_field.get_text().raw();
  std::string y_string = bspline_y_field.get_text().raw();
  // std::string z_string = wire_z_field.get_text().raw();

  int x_coord = atoi(x_string.c_str());
  int y_coord = atoi(y_string.c_str());
  // int z_coord = atoi(z_string.c_str());

  Coordinate p(x_coord, y_coord, 1);

  bspline_coord_list.push_back(p);

  bspline_x_field.set_text("");
  bspline_y_field.set_text("");

  std::string insert_a_coordinate_label_contents = "Added X : " + std::to_string(x_coord) + " Y : " + std::to_string(y_coord);

  LOG(4, insert_a_coordinate_label_contents.c_str());
  info_bspline_label.set_text(insert_a_coordinate_label_contents);

}

void AddObject::on_button_add_line3d()
{
	std::string x1_string = object3d_x1_field.get_text().raw();
	std::string y1_string = object3d_y1_field.get_text().raw();
	std::string z1_string = object3d_z1_field.get_text().raw();
	std::string x2_string = object3d_x2_field.get_text().raw();
	std::string y2_string = object3d_y2_field.get_text().raw();
	std::string z2_string = object3d_z2_field.get_text().raw();
	int x1_cord = atoi(x1_string.c_str());
	int y1_cord = atoi(y1_string.c_str());
	int z1_cord = atoi(z1_string.c_str());
	int x2_cord = atoi(x2_string.c_str());
	int y2_cord = atoi(y2_string.c_str());
	int z2_cord = atoi(z2_string.c_str());

  Coordinate begin(x1_cord, y1_cord, z1_cord);
  Coordinate end(x2_cord, y2_cord, z2_cord);
  object3d_coord_list.push_back(begin);
  object3d_coord_list.push_back(end);

  object3d_x1_field.set_text("");
  object3d_x2_field.set_text("");
  object3d_z1_field.set_text("");
  object3d_y1_field.set_text("");
  object3d_y2_field.set_text("");
  object3d_z2_field.set_text("");

  info_object3d_label.set_text(
    "Added X1:" + std::to_string(x1_cord) +
    " Y1:" + std::to_string(y1_cord) +
    " Z1:" + std::to_string(z1_cord) +
    " X2:" + std::to_string(x2_cord) +
    " Y2:" + std::to_string(y2_cord) +
    " Z2:" + std::to_string(z2_cord)
  );
}

void AddObject::on_button_save_object3d()
{
  if (object3d_coord_list.size() > 1)
  {
	  	std::string name = object3d_name_field.get_text().raw();
		if (name.empty())
		{
		  object3d_name_field.grab_focus();
		  return;
		}

		Coordinate border = this->_get_rgb_color(insert_border_color_field_r, insert_border_color_field_g, insert_border_color_field_b);
		Coordinate filling = this->_get_rgb_color(insert_filling_color_field_r, insert_filling_color_field_g, insert_filling_color_field_b);

		this->facade.addObject3D(name, object3d_coord_list, border, filling);
		this->facade.queue_draw();

		while(!object3d_coord_list.empty())
		{
			object3d_coord_list.pop_back();
		}

		this->window.close();
  }
  else
  {
   info_object3d_label.set_text("You need at least 1 line");
  }
}


