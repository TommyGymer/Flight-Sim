TEST_CASE("Vector arithmatic", "[fullMatrix]"){
    fullMatrix a = fullMatrix(MatrixType::Vector, 1, 2, 3);
    fullMatrix b = fullMatrix(MatrixType::Vector, 4, 5, 6);

    SECTION("get"){
        REQUIRE(a.x() == 1);
        REQUIRE(a.y() == 2);
        REQUIRE(a.x() == 3);
    }
}