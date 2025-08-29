Pod::Spec.new do |s|
  s.name             = "AlicloudPDNS"
  s.version          = "2.2.1"
  s.summary          = "阿里云公共DNS-SDK"
  s.homepage         = "https://help.aliyun.com/document_detail/181345.html"
  s.author           = { "路阳" => "ly02350553@alibaba-inc.com" }
  s.platform     = :ios
  s.ios.deployment_target = '10.0'
  s.source           = {
    :git => "https://github.com/aliyun/alibaba-pdns-sdk-ios.git",
    :tag => s.version.to_s
  }
  s.public_header_files = 'pdns-sdk-ios.framework/Headers/*.h'
  s.source_files        = 'pdns-sdk-ios.framework/Headers/*.{h}'
  s.vendored_frameworks = 'pdns-sdk-ios.framework'
  s.frameworks       = 'Foundation', 'CoreTelephony'
  s.xcconfig         = { 'OTHER_LDFLAGS' => '-ObjC' }
  s.requires_arc     = true
end
