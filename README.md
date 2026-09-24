# ImageProcessor 과제 제출

## 구현 항목
- Grayscale 변환: RGB 가중치 공식을 사용하여 회색조로 변환
- 밝기/대비 조절: 밝기 `30`, 대비 `1.2`를 적용하고 픽셀값을 `0~255` 범위로 제한
- 이진화(Thresholding): `0~255` 범위의 임계값을 입력받아 흑백으로 변환
- 3×3 Convolution 필터: Blur 및 Sharpen 커널을 직접 적용
- 히스토그램 분석: 밝기별 픽셀 개수를 계산하여 콘솔에 출력
- 이미지 크롭: 이미지의 왼쪽 위 영역을 원본 크기의 절반으로 잘라냄
- 이미지 리사이즈: 최근접 이웃 방식으로 원본 크기의 절반으로 축소
- 이미지 반전: 좌우, 상하, 상하·좌우 동시 반전 지원

# 선택 기능
- 필터 파이프라인: 쉼표로 구분한 여러 필터를 입력 순서대로 실행
- 추상 클래스 기반 설계: 이미지 필터가 `FilterBase`의 공통 인터페이스를 상속
- 멀티스레드 병렬 처리: Convolution 필터에서 이미지 행을 나누어 동시에 처리
- 로그 파일 출력: 필터 이름, 파라미터, 처리 시간, 성공/실패 여부와 오류 메시지를 `result.log`에 기록

## 지원 필터 이름

| 필터 이름 | 동작 |
| --- | --- |
| `grayscale` | 회색조 변환 |
| `brightness` | 밝기/대비 조절 |
| `threshold` | `--threshold`로 전달한 임계값을 사용하여 이진화 |
| `threshold:<값>` | 파이프라인 또는 단일 필터에서 임계값을 직접 지정 |
| `blur` | 3×3 평균 커널을 사용한 흐림 처리 |
| `sharpen` | 3×3 커널을 사용한 선명화 처리 |
| `histogram` | 밝기 히스토그램을 콘솔에 출력 |
| `crop` | 왼쪽 위 영역을 원본 크기의 절반으로 크롭 |
| `resize` | 원본 크기의 절반으로 리사이즈 |
| `flip-horizontal` | 좌우 반전 |
| `flip-vertical` | 상하 반전 |
| `flip-both` | 좌우 및 상하 반전 |

## 실행 명령어

아래 명령어는 `ImageProcessor_Starter_v4` 폴더에서 실행합니다.

```powershell
# Grayscale 변환
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_grayscale.bmp --filter grayscale

# 밝기/대비 조절
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_brightness.bmp --filter brightness

# 임계값 128로 이진화
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_threshold.bmp --filter threshold --threshold 128

# Blur 처리
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_blur.bmp --filter blur

# Sharpen 처리
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_sharpen.bmp --filter sharpen

# 히스토그램 출력
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_histogram.bmp --filter histogram

# 이미지 크롭
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_crop.bmp --filter crop

# 이미지 리사이즈
.\x64\Release\ImageProcessor.exe --input .\Resource\2_coffee.bmp --output .\Resource\2_coffee_resize.bmp --filter resize

# 좌우 반전
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\Resource\3_chelsea_cat_flip_horizontal.bmp --filter flip-horizontal

# 상하 반전
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\Resource\3_chelsea_cat_flip_vertical.bmp --filter flip-vertical

# 상하·좌우 동시 반전
.\x64\Release\ImageProcessor.exe --input .\Resource\3_chelsea_cat.bmp --output .\Resource\3_chelsea_cat_flip_both.bmp --filter flip-both

# 필터 파이프라인
.\x64\Release\ImageProcessor.exe --input .\Resource\1_astronaut.bmp --output .\Resource\1_astronaut_pipeline.bmp --pipeline "grayscale,threshold:128"
```

파이프라인 필터 이름 사이에는 공백을 넣지 않습니다.

## 로그 파일

프로그램을 실행하면 실행 폴더의 `result.log`에 로그가 누적됩니다.

```text
Filter: threshold
Parameters: threshold=128
Time: 3250 us
Result: success
--------------------
```