auto data = mstch::object{
  {"items", mstch::array{
    mstch::object{
      {"name", std::string{"name"}},
      {"items", mstch::array{1, 2, 3, 4}}
    }
  }}
};
