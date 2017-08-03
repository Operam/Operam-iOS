Pod::Spec.new do |s|
    s.name                  = "Operam"
    s.version               = "0.9.2"
    s.summary               = "User feedback solved."
    s.description           = "Feedback / bug reporting system for iOS applications with a developer productivity slant."
    s.homepage              = "https://operamhq.com"
    s.license               = { "type" => "Commercial", "text" => "See https://operamhq.com/terms-of-service"}
    s.author                = { "Operam" => "contact@operamhq.com" }
    s.source                = { "git" => "https://github.com/operam/Operam-iOS.git", :tag => s.version.to_s }
    s.platform              = :ios, '9.0'
    s.preserve_paths        = [ "Operam.framework/*" ]
    s.source_files          = "Operam.framework/Headers/*.{h}"
    s.public_header_files   = "Operam.framework/Headers/*.{h}"
    s.vendored_frameworks   = "Operam.framework"
    s.library               = "z"
end
