#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Parallelogram.h"

using namespace testing;

class ParallelogramTests : public::testing::Test {
    protected: 

        void SetUp() override {
            side1 = 2;
            side2 = 3;
            angle = 45;
            p_diffSideLength = new shapes::Parallelogram(shapes::Side(side1),shapes::Side(side2),shapes::Angle(angle));
            p_square = new shapes::Parallelogram(shapes::Side(side1),shapes::Side(side1),shapes::Angle(90));
        }

        void TearDown() override {
            delete p_diffSideLength;
            delete p_square;
        }

        int side1;
        int side2;
        float angle;
        shapes::Parallelogram* p_diffSideLength;
        shapes::Parallelogram* p_square;
};

TEST_F(ParallelogramTests, getPerimeterDiffLength) {
    EXPECT_EQ(p_diffSideLength->getPerimeter(), 2 * (side1 + side2));
}

TEST_F(ParallelogramTests, getAreaDiffLength) {
    EXPECT_EQ(p_diffSideLength->getArea(), side1 * side2 * sin((angle * M_PI) / 180.0));
}

TEST_F(ParallelogramTests, getKindPrecedence) {
    EXPECT_EQ(p_square->getKind(), shapes::Parallelogram::Kind::SQUARE);
}

