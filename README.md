# MFC_Homework3
1. 단일문서 기반의 프로그램을 작성한다.

  2. View에 입력하는 것은 마우스 버튼이다.
    - 왼쪽 마우스 버튼을 누른 상태에서 움직이면 움직임 따라 선이 그려진다(자유곡선). 곡선을 구성하는 점은 최대 10,000개
    - 자유곡선은 마우스왼쪽버튼 누름-움직임-해지에 따라 여러 개가 그려진다. 최대 100개
    - 마우스 오른쪽 버튼 누름 위치 – 해지 위치에 직선으로 선이 그려진다. 최대 100개 (직선)

  3. 파일 저장, 불러오기
    - 그려진 자유곡선과, 직선을 파일에 저장하고, 불러오기 기능도 구현한다.
    - 그려진 선들 모두 저장/불러오기 가능하도록 한다. 일부만 저장/불러오기 안됨.
    - 불러오기는 기존에 그려진 선들은 모두 무시하고, 파일에 저장된 것으로 대체한다.
    - 불러오기, 저장을 한 후에 다시 선을 추가하기도 가능하도록 한다. 예들 들어, 현재 자유곡선이 7개, 직선이 2개로 구성된 파일을 불러오기 하면, View에 9(7+2) 개의 선이 출력되는데, 여기에 자유곡선 3개, 직선 2개를 추가로 그리면, 자유곡선은 10개, 직선은 4개가 되어야 한다. 물론, 이것을 저장도 가능하게 한다.
