//
// Copyright (c) 2016-2017 Kris Jusiak (kris at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "GUnit/GTest.h"
#include "GUnit/GMake.h"
#include "../../public/hwclayer.h"

struct interface {
  virtual ~interface() = default;
  virtual void foo(int) const = 0;
  virtual void bar(int, const std::string&) const = 0;
};

struct HwcLayerS {
  virtual ~HwcLayerS() = default;
  virtual HwcLayerS& operator=(const HwcLayerS& rhs) = delete;
  virtual void SetNativeHandle(HWCNativeHandle handle) = 0;
  virtual HWCNativeHandle GetNativeHandle() const = 0;
  virtual void SetTransform(int32_t sf_transform) = 0;

  virtual void foo(int) const = 0;
  virtual void bar(int, const std::string&) const = 0;
};

class HwcLayerC {
  public:
    ~HwcLayerC(void) {};
    HwcLayerC(int data, HwcLayerS& l) : data(data), l(l) {}

    void update() {
      l.foo(42);
      l.bar(1, "str");
    }

    void setTransform() {
      l.SetTransform(77);
    }

    auto get_data() const { return data; }

  private:
    int data = {};
    HwcLayerS& l;
};

////////////////////////////////////////////////////////////////////////////////

GTEST(HwcLayerC) {

  // SetUp - Create sut and mocks if possible
  using namespace testing;
  std::tie(sut, mocks) = make<SUT, StrictGMock>(77);

  SHOULD("Simple foo bar") {
    EXPECT_CALL(mock<HwcLayerS>(), (foo)(42)).Times(1);
    EXPECT_CALL(mock<HwcLayerS>(), (bar)(_, "str"));
    sut->update();
  }

  SHOULD("fill hwclayer") {
    EXPECT_CALL(mock<HwcLayerS>(), (SetTransform)(77)).Times(1);
    sut->setTransform();
  }

  // TearDown
}


#if 0
  pHwcLayer->SetTransform(pParameter->transform);
  pHwcLayer->SetSourceCrop(hwcomposer::HwcRect<float>(
      pParameter->source_crop_x, pParameter->source_crop_y,
      pParameter->source_crop_width, pParameter->source_crop_height));
  pHwcLayer->SetDisplayFrame(hwcomposer::HwcRect<int>(
      pParameter->frame_x, pParameter->frame_y, pParameter->frame_width,
      pParameter->frame_height), 0, 0);
  pHwcLayer->SetNativeHandle(pRenderer->GetNativeBoHandle());
#endif

