auto data = mstch::object{
  {"terms", mstch::array{
    mstch::object{{"name", std::string{"t1"}}, {"index", 0}},
    mstch::object{{"name", std::string{"t2"}}, {"index", 1}}
  }}
};
