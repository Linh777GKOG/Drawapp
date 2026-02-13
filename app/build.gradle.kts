plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "com.example.drawapp"

    // SỬA: Dùng syntax chuẩn để tránh lỗi build
    compileSdk = 35

    defaultConfig {
        applicationId = "com.example.drawapp"
        minSdk = 24
        targetSdk = 35 // Nên khớp với compileSdk
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"

        // THÊM: Cấu hình quan trọng cho C++
        externalNativeBuild {
            cmake {
                // Bắt buộc dùng C++17 trở lên cho các dự án đồ họa hiện đại
                cppFlags += "-std=c++17"

                // (Tùy chọn) Chỉ build cho các dòng máy phổ biến để build nhanh hơn
                // abiFilters += listOf("arm64-v8a", "x86_64") 
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }

    // Đường dẫn tới file CMakeLists.txt (Giữ nguyên)
    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }

    buildFeatures {
        viewBinding = true
    }
}

dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.appcompat)
    implementation(libs.material)
    implementation(libs.androidx.constraintlayout)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
}