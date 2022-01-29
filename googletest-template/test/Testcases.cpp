#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Parallelogram.h"
#include "Matthews.h"
#include "Awards.h"
#include <string>

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

////////////

TEST(MatthewsTests, reachZero) {
    EXPECT_EQ(sequence::checkMatthewsOutcome(3), sequence::MatthewsOutcome::ZERO);
    EXPECT_EQ(sequence::checkMatthewsOutcome(4), sequence::MatthewsOutcome::ZERO);
    EXPECT_EQ(sequence::checkMatthewsOutcome(5), sequence::MatthewsOutcome::ZERO);
}

TEST(MatthewsTests, reachMinusOneCycle) {
    EXPECT_EQ(sequence::checkMatthewsOutcome(-1), sequence::MatthewsOutcome::MINUS_ONE_CYCLE);
}

TEST(MatthewsTests, reachMinusTwoCycle) {
    EXPECT_EQ(sequence::checkMatthewsOutcome(-2), sequence::MatthewsOutcome::MINUS_TWO_CYCLE);
    EXPECT_EQ(sequence::checkMatthewsOutcome(-4), sequence::MatthewsOutcome::MINUS_TWO_CYCLE);
}

////////////

class RankListStub : public awards::RankList {
    public:

        RankListStub() { callnum = 0; }

        std::string getNext() {
            std::string name = "participant" + std::to_string(callnum);
            callnum++;
            return name;
        } 
    private:
        int callnum;
};

class MockAwardCeremonyActions : public awards::AwardCeremonyActions {
    public:
        MOCK_METHOD(void, playAnthem, (), (override));
        MOCK_METHOD(void, turnOffTheLightsAndGoHome, (), (override));
        MOCK_METHOD(void, awardBronze, (std::string recipient), (override));
        MOCK_METHOD(void, awardSilver, (std::string recipient), (override));
        MOCK_METHOD(void, awardGold, (std::string recipient), (override));
};

TEST(AwardsTests, testCeremony) {
    MockAwardCeremonyActions ceremony;
    RankListStub participants;

    {
        InSequence seq;
        EXPECT_CALL(ceremony, playAnthem()).Times(1);
        EXPECT_CALL(ceremony, awardBronze("participant0")).Times(1);
        EXPECT_CALL(ceremony, awardSilver("participant1")).Times(1);
        EXPECT_CALL(ceremony, awardGold("participant2")).Times(1);
        EXPECT_CALL(ceremony, turnOffTheLightsAndGoHome()).Times(1);
    }
    
    awards::performAwardCeremony(participants, ceremony);
}